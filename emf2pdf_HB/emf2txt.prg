#include <fivewin.ch>
#include <fileio.ch>

static nFile
* https://msdn.microsoft.com/en-us/library/cc231166.aspx
* c:\Program Files (x86)\Windows Kits\8.1\Include\um\wingdi.h
proc main(cBase)
    LOCAL hDC, hMeta
    if empty(cBase)
        cBase := "ReportStandard"
    endif
    if lower(right(cBase,4))==".emf"
        cBase := left(cBase,len(cBase)-4)
    endif
    if !file(cBase+".emf")
        ? "file not found"
        return
    endif
    hDC := CreateDC( "DISPLAY",0,0,0)
    hMeta := GetEnhMetaFile(cBase+".emf")
    if file(cBase+".txt")
        fErase(cBase+".txt")
    endif
    fclose(fcreate(cBase+".txt"))
    nFile := fopen(cBase+".txt", FO_WRITE + FO_DENYWRITE)
    EnumEnhMetaFile(hDC,hMeta,{|pDC,pTable,pRECORD| MyCB(pDC,pTable,pRECORD) },{0,0,100,100})
    fClose(nFile)

func MyCB(pDC,pTable,pRECORD)
    LOCAL i,cOut := "Record " + cValToChar(pRecord[1])
    switch pRecord[1]
        case 10 //EMR_SETWINDOWORGEX
            cOut += "-SetWindowOrg " + cValToChar(pRecord[2]) + "," + cValToChar(pRecord[3])
            exit
        case 18 // EMR_SETBKMODE
            cOut += "-SetBKMode " + cValToChar(pRecord[2])
            switch pRecord[2]
                case 1
                    cOut += " TRANSPARENT"
                    exit
                case 2
                    cOut += " OPAQUE"
                    exit
                otherwise
                    cOut += " unknown"
                    exit
            endswitch
            exit
        case 12 // EMR_SETVIEWPORTORGEX
            cOut += "-SetViewportOrg " + cValToChar(pRecord[2]) + "," + cValToChar(pRecord[3])
            exit
        case 13 // EMR_SETBRUSHORGEX
            cOut += "-SetBrushOrg " + cValToChar(pRecord[2]) + "," + cValToChar(pRecord[3])
            exit
        case 20 // EMR_SETROP2
            cOut += "-SetRop " + GetRopName(pRecord[2])
            exit

        case 21 // EMR_SETSTRETCHBLTMODE
            cOut += "-SetStretchBltMode "
            switch pRecord[2]
                case 1
                    cOut += " ANDSCANS"
                    exit
                case 2
                    cOut += " ORSCANS"
                    exit
                case 3
                    cOut += " ORSCANS"
                    exit
                case 4
                    cOut += " HALFTONE"
                    exit
                otherwise
                    cOut +=  cValToChar(pRecord[2]) + " unknown"
                    exit
            endswitch
            exit
        case 22 // EMR_SETTEXTALIGN
            cOut += "-SetTextAlign 0x" + HB_NUMTOHEX(pRecord[2],4)
            cOut += GetAlignName(pRecord[2])
            exit
        case 24 // EMR_SETTEXTCOLOR
            cOut += "-SetTextColor 0x" + HB_NUMTOHEX(pRecord[2],8)
            exit
        case 27 // EMR_MOVETOEX
            cOut += "-MoveTo " + cValToChar(pRecord[2]) + "," + cValToChar(pRecord[3])
            exit
        case 30 // EMR_INTERSECTCLIPRECT
            cOut += "-IntersectRect [" + cValToChar(pRecord[2]) + "," + cValToChar(pRecord[3]) + "," + cValToChar(pRecord[4]) + "," + cValToChar(pRecord[5]) + "]"
            exit
        case 33 // EMR_SAVEDC
            cOut += "-SaveDC"
            exit
        case 34 // EMR_RESTOREDC
            cOut += "-RestoreDC " + cValToChar(-(0xFFFFFFFF-pRecord[2]+1))
            exit
        case 37 // EMR_SELECTOBJECT
            cOut += "-SelectObject 0x" + HB_NUMTOHEX(pRecord[2],8)
            cOut += GetStockName(pRecord[2])
            exit
        case 38 // EMR_CREATEPEN
            cOut += "-CreatePen " + cValToChar(pRecord[2])
            cOut += GetPenStyle(pRecord[3])
            cOut += " Width: " + cValToChar(pRecord[4])
            cOut += " Color 0x" + HB_NUMTOHEX(pRecord[6],8)
            pTable[pRecord[2]] := 38
            exit
        case 39 // EMR_CREATEBRUSHINDIRECT
            cOut += "-CreateBrush " + cValToChar(pRecord[2])
            cOut += GetBrushStyle(pRecord[3])
            cOut += " Color 0x" + HB_NUMTOHEX(pRecord[4],8)
            cOut += " Info: " + cValToChar(pRecord[5])
            pTable[pRecord[2]] := 39
            exit
        case 54 // EMR_LINETO
            cOut += "-LineTo " + cValToChar(pRecord[2]) + "," + cValToChar(pRecord[3])
            exit
        case 76 // EMR_BITBLT
            cOut += "-BitBlt"
            cOut += " ["+cValToChar(pRecord[2])+","+cValToChar(pRecord[3])+","+cValToChar(pRecord[4])+","+cValToChar(pRecord[5])+"]"
            cOut += " ["+cValToChar(pRecord[6])+","+cValToChar(pRecord[7])+","+cValToChar(pRecord[8])+","+cValToChar(pRecord[9])+"]"
            cOut += GetTernary(pRecord[10]) + " 0x" + HB_NUMTOHEX(pRecord[10],8)
            exit
        case 82 // EMR_EXTCREATEFONTINDIRECTW
            cOut += "-CreateFont " + cValToChar(pRecord[2])
            cOut += " Height: " + cValToChar(pRecord[3])
            cOut += " Width: " + cValToChar(pRecord[4])
            cOut += " Escapement: " + cValToChar(pRecord[5])
            cOut += " Orientation: " + cValToChar(pRecord[6])
            cOut += " Weight: " + cValToChar(pRecord[7])
            cOut += " Italic: " + cValToChar(hb_bitShift(hb_bitAnd(pRecord[8],0x0FF),0))
            cOut += " Underline: " + cValToChar(hb_bitShift(hb_bitAnd(pRecord[8],0x0FF00),-8))
            cOut += " StrikeOut: " + cValToChar(hb_bitShift(hb_bitAnd(pRecord[8],0x0FF0000),-16))
            cOut += " CharSet: " + cValToChar(hb_bitShift(hb_bitAnd(pRecord[8],0x0FF000000),-24))
            cOut += " OutPrecision: " + cValToChar(hb_bitShift(hb_bitAnd(pRecord[9],0x0FF),0))
            cOut += " ClipPrecision: " + cValToChar(hb_bitShift(hb_bitAnd(pRecord[9],0x0FF00),-8))
            cOut += " Quality: " + cValToChar(hb_bitShift(hb_bitAnd(pRecord[9],0x0FF0000),-16))
            cOut += " PitchAndFamily: " + cValToChar(hb_bitShift(hb_bitAnd(pRecord[9],0x0FF000000),-24))
            cOut += " Facename: " + ReadW(pRecord,10,32)
            pTable[pRecord[2]] := 82
            exit
        case 84 // EMR_EXTTEXTOUTW
            cOut += "-ExtTextOut"
            cOut += " ["+cValToChar(pRecord[2])+","+cValToChar(pRecord[3])+","+cValToChar(pRecord[4])+","+cValToChar(pRecord[5])+"]"
            cOut += GetGraphicsModeName(pRecord[6])
            cOut += " Scale " + cValToChar(GetFloat(pRecord[7])) + ","  + cValToChar(GetFloat(pRecord[8])) 
            i:=9
            //while i<len(pRecord)
                cOut += " pos " + cValToChar(pRecord[i+0]) + "," + cValToChar(pRecord[i+1])
                cOut += " len " + cValToChar(pRecord[i+2])
                cOut += " offStr " + cValToChar(pRecord[i+3])
                cOut += " opt " + GetTextOutOptions(pRecord[i+4])
                cOut += " rect ["+cValToChar(pRecord[i+5])+","+cValToChar(pRecord[i+6])+","+cValToChar(pRecord[i+7])+","+cValToChar(pRecord[i+8])+"]"
                cOut += " offDX " + cValToChar(pRecord[i+9])
                cOut += " '"+ReadW(pRecord,i+10,pRecord[i+2])+"'"
                cOut += " DX " + WriteBytes(pRecord,pRecord[i+9],pRecord[i+2])
            //enddo
                // [1320,120,3639,185],1,[1082619105,1082619449],[1320,120],80nChar,76Off,0Opt,[0,0,4294967295,4294967295],236, 2097194,6619220,7209059,2097263,7274572,6881383,6357091,2752544,2097184,2097184,2097184,2097184,2097184,2097184,8126496,2752544,5046304,4653121,5898305,4784218,5177422,2097184,3801137,5046304,7471201,6619243,2097268,6357075,2097262,7274578,6488163,2097263,2097194,3342386,3211311,3080240,3670065,3211296,3801144,3670067,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,37,12 - pTable -1807341281,0,0,0,0
                //  2    3    4   5    6   7           8            9   10    11     12    13   1415  16         17        18    19 
            exit
        case 98 // EMR_SETICMMODE
            cOut += "-SetICMMode"+ cValToChar(pRecord[2])
            switch pRecord[2]
                case 1
                    cOut += " OFF"
                    exit
                case 2
                    cOut += " ON"
                    exit
                case 3
                    cOut += " QUERY"
                    exit
                case 4
                    cOut += " DONE_OUTSIDEDC"
                    exit
                otherwise
                    cOut += " unknown"
                    exit
            endswitch            
        otherwise
            for i:=2 to len(pRECORD)
                cOut += ","+ cValToChar(pRecord[i])
            next
            endswitch
    cOut += " - pTable " + cValToChar(pTable[1])
    for i:=2 to len(pTable)
        cOut += ","+ cValToChar(pTable[i])
    next
    cOut += CRLF
    fWrite(nFile,cOut,len(cOut))
return 1

func ReadW(aRecord,nStart,nLen)
    LOCAL c, i, cRet := "", v
    for i:=0 to nLen/2-1
        c := aRecord[nStart+i]
        if c>0
            v := hb_bitAnd(c,0x0FFFF)
            if v>0
                cRet += Chr(v)
            else
                exit
            endif
            v := hb_bitShift(hb_bitAnd(c,0x0FFFF0000),-16)
            if v>0
                cRet += Chr(v)
            else
                exit
            endif
        else
            exit
        endif
    next
    if hb_bitand(nLen,1)>0
        c := aRecord[nStart+ nLen/2]
        v := hb_bitAnd(c,0x0FFFF)
        if v>0
            cRet += Chr(v)
        endif
    endif
return cRet

function WriteBytes(pRecord,start,len)
    LOCAL cOut := "",i
    start /=4
    for i:=0 to len-1
        if len(pRecord)<start+i
            exit
        endif
        cOut += cValToChar(pRecord[start+i])+", "
    next
return cOut

func GetStockName(i)
    if i<0x80000000
        return ""
    endif
    switch hb_bitAnd(i,0xFF)
    case 0x00
            return " WHITE_BRUSH "
    case 0x01
        return " LTGRAY_BRUSH"
    case 0x02 
        return " GRAY_BRUSH"
    case 0x03 
        return " DKGRAY_BRUSH"
    case 0x04 
        return " BLACK_BRUSH"
    case 0x05 
        return " NULL_BRUSH"
    case 0x06 
        return " WHITE_PEN"
    case 0x07 
        return " BLACK_PEN"
    case 0x08 
        return " NULL_PEN"
    case 0x0A 
        return " OEM_FIXED_FONT"
    case 0x0B 
        return " ANSI_FIXED_FONT"
    case 0x0C 
        return " ANSI_VAR_FONT"
    case 0x0D 
        return " SYSTEM_FONT"
    case 0x0E 
        return " DEVICE_DEFAULT_FONT"
    case 0x0F 
        return " DEFAULT_PALETTE"
    case 0x10 
        return " SYSTEM_FIXED_FONT"
    case 0x11 
        return " DEFAULT_GUI_FONT"
    case 0x12 
        return " DC_BRUSH"
    case 0x13
        return " DC_PEN"
    endswitch
return ""

FUNC GetAlignName(i)
    local cRet :="", n
    if hb_bitAnd(i,1)>0
        cRet+="updatecp"
    endif
    n:=hb_bitAnd(i,6)
    switch n
        case 0
            cRet += " Left"
            exit
        case 2
            cRet += " Right"
            exit
        case 6
            cRet += " Center"
            exit
    endswitch
    n:=hb_bitAnd(i,0x18)
    switch n
        case 0
            cRet += " Top"
            exit
        case 8
            cRet += " Bottom"
            exit
        case 0x18
            cRet += " Baseline"
            exit
    endswitch
    if hb_bitAnd(i,0x100)>0
        cRet+=" RTL"
    endif
return cRet

func GetGraphicsModeName(i)
    switch i
        case 1
            return " COMPATIBLE"
        case 2
            return " ADVANCED"
    endswitch
return " unknown"

func GetPenStyle(i)
    LOCAL cRet := ""
    switch hb_bitAnd(i,0xF)
        case 0x00000000
            cRet+=" solid"
            exit
        case 0x00000001
            cRet+=" dash"
            exit
        case 0x00000002
            cRet+=" dot"
            exit
        case 0x00000003
            cRet+=" dashdot"
            exit
        case 0x00000004
            cRet+=" dashdotdot"
            exit
        case 0x00000005
            cRet+=" null"
            exit
        case 0x00000006
            cRet+=" insideframe"
            exit
        case 0x00000007
            cRet+=" userstyle"
            exit
        case 0x00000008
            cRet+=" alternate"
            exit
    endswitch
    switch hb_bitShift(HB_bitAnd(i,0xF00),-8)
        case 0x000000
            cRet+=" endcap round"
            exit
        case 0x000001
            cRet+=" endcap_square"
            exit
        case 0x000002
            cRet+=" endcap_flat"
            exit
    endswitch
    switch hb_bitShift(HB_bitAnd(i,0xF000),-12)
        case 0x00000
            cRet+=" join_round"
            exit
        case 0x00001
            cRet+=" join_bevel"
            exit
        case 0x00002
            cRet+=" join_miter"
            exit
    endswitch
    switch hb_bitShift(HB_bitAnd(i,0xF0000),-16)
        case 0x00000000
            cRet+=" cosmetic"
            exit
        case 0x00010000
            cRet+=" geometric"
            exit
    endswitch
return  cRet

func GetBrushStyle(i)
    switch(i)
        case 0x0000
            return " SOLID"
        case 0x0001
            return " NULL"
        case 0x0002
            return " HATCHED"
        case 0x0003
            return " PATTERN"
        case 0x0004
            return " INDEXED"
        case 0x0005
            return " DIBPATTERN"
        case 0x0006
            return " DIBPATTERNPT"
        case 0x0007
            return " PATTERN8X8"
        case 0x0008
            return " DIBPATTERN8X8"
        case 0x0009
            return " MONOPATTERN"
    endswitch
return " unknown"

func GetTernary(i)
    switch hb_bitShift(HB_bitAnd(i,0xFF0000),-16)
        case 0x00
            return " BLACKNESS"
        case 0x01
            return " DPSOON"
        case 0x02
            return " DPSONA"
        case 0x03
            return " PSON"
        case 0x04
            return " SDPONA"
        case 0x05
            return " DPON"
        case 0x06
            return " PDSXNON"
        case 0x07
            return " PDSAON"
        case 0x08
            return " SDPNAA"
        case 0x09
            return " PDSXON"
        case 0x0A
            return " DPNA"
        case 0x0B
            return " PSDNAON"
        case 0x0C
            return " SPNA"
        case 0x0D
            return " PDSNAON"
        case 0x0E
            return " PDSONON"
        case 0x0F
            return " PN"
        case 0x10
            return " PDSONA"
        case 0x11
            return " NOTSRCERASE"
        case 0x12
            return " SDPXNON"
        case 0x13
            return " SDPAON"
        case 0x14
            return " DPSXNON"
        case 0x15
            return " DPSAON"
        case 0x16
            return " PSDPSANAXX"
        case 0x17
            return " SSPXDSXAXN"
        case 0x18
            return " SPXPDXA"
        case 0x19
            return " SDPSANAXN"
        case 0x1A
            return " PDSPAOX"
        case 0x1B
            return " SDPSXAXN"
        case 0x1C
            return " PSDPAOX"
        case 0x1D
            return " DSPDXAXN"
        case 0x1E
            return " PDSOX"
        case 0x1F
            return " PDSOAN"
        case 0x20
            return " DPSNAA"
        case 0x21
            return " SDPXON"
        case 0x22
            return " DSNA"
        case 0x23
            return " SPDNAON"
        case 0x24
            return " SPXDSXA"
        case 0x25
            return " PDSPANAXN"
        case 0x26
            return " SDPSAOX"
        case 0x27
            return " SDPSXNOX"
        case 0x28
            return " DPSXA"
        case 0x29
            return " PSDPSAOXXN"
        case 0x2A
            return " DPSANA"
        case 0x2B
            return " SSPXPDXAXN"
        case 0x2C
            return " SPDSOAX"
        case 0x2D
            return " PSDNOX"
        case 0x2E
            return " PSDPXOX"
        case 0x2F
            return " PSDNOAN"
        case 0x30
            return " PSNA"
        case 0x31
            return " SDPNAON"
        case 0x32
            return " SDPSOOX"
        case 0x33
            return " NOTSRCCOPY"
        case 0x34
            return " SPDSAOX"
        case 0x35
            return " SPDSXNOX"
        case 0x36
            return " SDPOX"
        case 0x37
            return " SDPOAN"
        case 0x38
            return " PSDPOAX"
        case 0x39
            return " SPDNOX"
        case 0x3A
            return " SPDSXOX"
        case 0x3B
            return " SPDNOAN"
        case 0x3C
            return " PSX"
        case 0x3D
            return " SPDSONOX"
        case 0x3E
            return " SPDSNAOX"
        case 0x3F
            return " PSAN"
        case 0x40
            return " PSDNAA"
        case 0x41
            return " DPSXON"
        case 0x42
            return " SDXPDXA"
        case 0x43
            return " SPDSANAXN"
        case 0x44
            return " SRCERASE"
        case 0x45
            return " DPSNAON"
        case 0x46
            return " DSPDAOX"
        case 0x47
            return " PSDPXAXN"
        case 0x48
            return " SDPXA"
        case 0x49
            return " PDSPDAOXXN"
        case 0x4A
            return " DPSDOAX"
        case 0x4B
            return " PDSNOX"
        case 0x4C
            return " SDPANA"
        case 0x4D
            return " SSPXDSXOXN"
        case 0x4E
            return " PDSPXOX"
        case 0x4F
            return " PDSNOAN"
        case 0x50
            return " PDNA"
        case 0x51
            return " DSPNAON"
        case 0x52
            return " DPSDAOX"
        case 0x53
            return " SPDSXAXN"
        case 0x54
            return " DPSONON"
        case 0x55
            return " DSTINVERT"
        case 0x56
            return " DPSOX"
        case 0x57
            return " DPSOAN"
        case 0x58
            return " PDSPOAX"
        case 0x59
            return " DPSNOX"
        case 0x5A
            return " PATINVERT"
        case 0x5B
            return " DPSDONOX"
        case 0x5C
            return " DPSDXOX"
        case 0x5D
            return " DPSNOAN"
        case 0x5E
            return " DPSDNAOX"
        case 0x5F
            return " DPAN"
        case 0x60
            return " PDSXA"
        case 0x61
            return " DSPDSAOXXN"
        case 0x62
            return " DSPDOAX"
        case 0x63
            return " SDPNOX"
        case 0x64
            return " SDPSOAX"
        case 0x65
            return " DSPNOX"
        case 0x66
            return " SRCINVERT"
        case 0x67
            return " SDPSONOX"
        case 0x68
            return " DSPDSONOXXN"
        case 0x69
            return " PDSXXN"
        case 0x6A
            return " DPSAX"
        case 0x6B
            return " PSDPSOAXXN"
        case 0x6C
            return " SDPAX"
        case 0x6D
            return " PDSPDOAXXN"
        case 0x6E
            return " SDPSNOAX"
        case 0x6F
            return " PDXNAN"
        case 0x70
            return " PDSANA"
        case 0x71
            return " SSDXPDXAXN"
        case 0x72
            return " SDPSXOX"
        case 0x73
            return " SDPNOAN"
        case 0x74
            return " DSPDXOX"
        case 0x75
            return " DSPNOAN"
        case 0x76
            return " SDPSNAOX"
        case 0x77
            return " DSAN"
        case 0x78
            return " PDSAX"
        case 0x79
            return " DSPDSOAXXN"
        case 0x7A
            return " DPSDNOAX"
        case 0x7B
            return " SDPXNAN"
        case 0x7C
            return " SPDSNOAX"
        case 0x7D
            return " DPSXNAN"
        case 0x7E
            return " SPXDSXO"
        case 0x7F
            return " DPSAAN"
        case 0x80
            return " DPSAA"
        case 0x81
            return " SPXDSXON"
        case 0x82
            return " DPSXNA"
        case 0x83
            return " SPDSNOAXN"
        case 0x84
            return " SDPXNA"
        case 0x85
            return " PDSPNOAXN"
        case 0x86
            return " DSPDSOAXX"
        case 0x87
            return " PDSAXN"
        case 0x88
            return " SRCAND"
        case 0x89
            return " SDPSNAOXN"
        case 0x8A
            return " DSPNOA"
        case 0x8B
            return " DSPDXOXN"
        case 0x8C
            return " SDPNOA"
        case 0x8D
            return " SDPSXOXN"
        case 0x8E
            return " SSDXPDXAX"
        case 0x8F
            return " PDSANAN"
        case 0x90
            return " PDSXNA"
        case 0x91
            return " SDPSNOAXN"
        case 0x92
            return " DPSDPOAXX"
        case 0x93
            return " SPDAXN"
        case 0x94
            return " PSDPSOAXX"
        case 0x95
            return " DPSAXN"
        case 0x96
            return " DPSXX"
        case 0x97
            return " PSDPSONOXX"
        case 0x98
            return " SDPSONOXN"
        case 0x99
            return " DSXN"
        case 0x9A
            return " DPSNAX"
        case 0x9B
            return " SDPSOAXN"
        case 0x9C
            return " SPDNAX"
        case 0x9D
            return " DSPDOAXN"
        case 0x9E
            return " DSPDSAOXX"
        case 0x9F
            return " PDSXAN"
        case 0xA0
            return " DPA"
        case 0xA1
            return " PDSPNAOXN"
        case 0xA2
            return " DPSNOA"
        case 0xA3
            return " DPSDXOXN"
        case 0xA4
            return " PDSPONOXN"
        case 0xA5
            return " PDXN"
        case 0xA6
            return " DSPNAX"
        case 0xA7
            return " PDSPOAXN"
        case 0xA8
            return " DPSOA"
        case 0xA9
            return " DPSOXN"
        case 0xAA
            return " D"
        case 0xAB
            return " DPSONO"
        case 0xAC
            return " SPDSXAX"
        case 0xAD
            return " DPSDAOXN"
        case 0xAE
            return " DSPNAO"
        case 0xAF
            return " DPNO"
        case 0xB0
            return " PDSNOA"
        case 0xB1
            return " PDSPXOXN"
        case 0xB2
            return " SSPXDSXOX"
        case 0xB3
            return " SDPANAN"
        case 0xB4
            return " PSDNAX"
        case 0xB5
            return " DPSDOAXN"
        case 0xB6
            return " DPSDPAOXX"
        case 0xB7
            return " SDPXAN"
        case 0xB8
            return " PSDPXAX"
        case 0xB9
            return " DSPDAOXN"
        case 0xBA
            return " DPSNAO"
        case 0xBB
            return " MERGEPAINT"
        case 0xBC
            return " SPDSANAX"
        case 0xBD
            return " SDXPDXAN"
        case 0xBE
            return " DPSXO"
        case 0xBF
            return " DPSANO"
        case 0xC0
            return " MERGECOPY"
        case 0xC1
            return " SPDSNAOXN"
        case 0xC2
            return " SPDSONOXN"
        case 0xC3
            return " PSXN"
        case 0xC4
            return " SPDNOA"
        case 0xC5
            return " SPDSXOXN"
        case 0xC6
            return " SDPNAX"
        case 0xC7
            return " PSDPOAXN"
        case 0xC8
            return " SDPOA"
        case 0xC9
            return " SPDOXN"
        case 0xCA
            return " DPSDXAX"
        case 0xCB
            return " SPDSAOXN"
        case 0xCC
            return " SRCCOPY"
        case 0xCD
            return " SDPONO"
        case 0xCE
            return " SDPNAO"
        case 0xCF
            return " SPNO"
        case 0xD0
            return " PSDNOA"
        case 0xD1
            return " PSDPXOXN"
        case 0xD2
            return " PDSNAX"
        case 0xD3
            return " SPDSOAXN"
        case 0xD4
            return " SSPXPDXAX"
        case 0xD5
            return " DPSANAN"
        case 0xD6
            return " PSDPSAOXX"
        case 0xD7
            return " DPSXAN"
        case 0xD8
            return " PDSPXAX"
        case 0xD9
            return " SDPSAOXN"
        case 0xDA
            return " DPSDANAX"
        case 0xDB
            return " SPXDSXAN"
        case 0xDC
            return " SPDNAO"
        case 0xDD
            return " SDNO"
        case 0xDE
            return " SDPXO"
        case 0xDF
            return " SDPANO"
        case 0xE0
            return " PDSOA"
        case 0xE1
            return " PDSOXN"
        case 0xE2
            return " DSPDXAX"
        case 0xE3
            return " PSDPAOXN"
        case 0xE4
            return " SDPSXAX"
        case 0xE5
            return " PDSPAOXN"
        case 0xE6
            return " SDPSANAX"
        case 0xE7
            return " SPXPDXAN"
        case 0xE8
            return " SSPXDSXAX"
        case 0xE9
            return " DSPDSANAXXN"
        case 0xEA
            return " DPSAO"
        case 0xEB
            return " DPSXNO"
        case 0xEC
            return " SDPAO"
        case 0xED
            return " SDPXNO"
        case 0xEE
            return " SRCPAINT"
        case 0xEF
            return " SDPNOO"
        case 0xF0
            return " PATCOPY"
        case 0xF1
            return " PDSONO"
        case 0xF2
            return " PDSNAO"
        case 0xF3
            return " PSNO"
        case 0xF4
            return " PSDNAO"
        case 0xF5
            return " PDNO"
        case 0xF6
            return " PDSXO"
        case 0xF7
            return " PDSANO"
        case 0xF8
            return " PDSAO"
        case 0xF9
            return " PDSXNO"
        case 0xFA
            return " DPO"
        case 0xFB
            return " PATPAINT"
        case 0xFC
            return " PSO"
        case 0xFD
            return " PSDNOO"
        case 0xFE
            return " DPSOO"
        case 0xFF
            return " WHITENESS"
    endswitch
return " unknown" + cValToChar(i)

func GetRopName(i)
    switch(i)
        case 0x0001
            return "BLACK"
        case 0x0002
            return "NOTMERGEPEN"
        case 0x0003
            return "MASKNOTPEN"
        case 0x0004
            return "NOTCOPYPEN"
        case 0x0005
            return "MASKPENNOT"
        case 0x0006
            return "NOT"
        case 0x0007
            return "XORPEN"
        case 0x0008
            return "NOTMASKPEN"
        case 0x0009
            return "MASKPEN"
        case 0x000A
            return "NOTXORPEN"
        case 0x000B
            return "NOP"
        case 0x000C
            return "MERGENOTPEN"
        case 0x000D
            return "COPYPEN"
        case 0x000E
            return "MERGEPENNOT"
        case 0x000F
            return "MERGEPEN"
        case 0x0010
            return "WHITE"        
    endswitch
return " unknown" + cValToChar(i)

func GetTextOutOptions(i)
    LOCAL cOut:=""
    cOut += iif(hb_bitAnd(i,0x00000002)>0," OPAQUE","")
    cOut += iif(hb_bitAnd(i,0x00000004)>0," CLIPPED","")
    cOut += iif(hb_bitAnd(i,0x00000010)>0," GLYPH_INDEX","")
    cOut += iif(hb_bitAnd(i,0x00000080)>0," RTLREADING","")
    cOut += iif(hb_bitAnd(i,0x00000100)>0," NO_RECT","")
    cOut += iif(hb_bitAnd(i,0x00000200)>0," SMALL_CHARS","")
    cOut += iif(hb_bitAnd(i,0x00000400)>0," NUMERICSLOCAL","")
    cOut += iif(hb_bitAnd(i,0x00000800)>0," NUMERICSLATIN","")
    cOut += iif(hb_bitAnd(i,0x00001000)>0," IGNORELANGUAGE","")
    cOut += iif(hb_bitAnd(i,0x00002000)>0," PDY","")
    cOut += iif(hb_bitAnd(i,0x00010000)>0," REVERSE_INDEX_MAP","")    
return cOut

#pragma begindump
#include <windows.h>
#include <hbapi.h>
#include <hbapiitm.h>
#include <hbstack.h>

#ifndef _WIN64
#define hb_parfw hb_parnl
#define hb_itempPutFw hb_itemPutNL
#define hb_itempGetFw hb_itemGetNL
#define FWCAST long
#else
#define hb_parfw hb_parnll
#define hb_itempPutFw hb_itemPutNLL
#define hb_itempGetFw hb_itemGetNLL
#define FWCAST long long
#endif

int CALLBACK HBEnhEnumProc(HDC hDC,HANDLETABLE *lpHTable,const ENHMETARECORD *lpEMFR,int nObj,LPARAM lpData)
{
    PHB_ITEM pBlock = (PHB_ITEM)lpData;
    PHB_ITEM pDC = hb_itempPutFw(0,(FWCAST)hDC);
    PHB_ITEM pHandleTable = hb_itemArrayNew(nObj);
    PHB_ITEM pRecord = hb_itemArrayNew(lpEMFR->nSize/4+1);
    PHB_ITEM pRet;
    int i;
    for(i=0;i<nObj;i++)
        hb_itemArrayPut(pHandleTable,i+1,hb_itempPutFw(0,(FWCAST)lpHTable->objectHandle[i]));
        
    hb_itemArrayPut(pRecord,1,hb_itemPutNI(0,lpEMFR->iType));
    for(i=0;i<(int)lpEMFR->nSize/4;i++)
        hb_itemArrayPut(pRecord,i+2,hb_itemPutNInt(0,lpEMFR->dParm[i]));

    hb_evalBlock(pBlock, pDC, pHandleTable, pRecord, 0);

    for(i=0;i<nObj;i++)
        lpHTable->objectHandle[i] = (HGDIOBJ)hb_itempGetFw(hb_itemArrayGet(pHandleTable,i+1));

    pRet = hb_stackReturnItem();
    if HB_IS_NUMBER(pRet)
    {
        return hb_itemGetNI(pRet);
    }
    else
    {
        return 0;
    }
}

HB_FUNC( ENUMENHMETAFILE )
{
    RECT rect;
    rect.top    = hb_parvni( 4, 1);
    rect.left   = hb_parvni( 4, 2);
    rect.bottom = hb_parvni( 4, 3);
    rect.right  = hb_parvni( 4, 4);
    EnumEnhMetaFile((HDC)hb_parfw(1),(HENHMETAFILE)hb_parfw(2),HBEnhEnumProc, hb_param( 3, HB_IT_BLOCK ),&rect);
    hb_ret();
}


HB_FUNC( GETFLOAT )
{
    union {
        float f;
        int i;
    } tmp;
    tmp.i = hb_parni(1);
    hb_retnd(tmp.f);
}
#pragma enddump
