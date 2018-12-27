#include <fivewin.ch>
#include <fileio.ch>
#include <harupdf.ch>
//#require "hbhpdf"

static fontList
static aCreated := {}
static xScale, yScale, currFont, currX, currY
* https://msdn.microsoft.com/en-us/library/cc231166.aspx
* c:\Program Files (x86)\Windows Kits\8.1\Include\um\wingdi.h

// test's main 
func main(cBase)
    LOCAL hDC, hMeta, f
    LOCAL pdf, page, aFiles, cPDF
    if empty(cBase)
        cBase := "ReportStandard"
    endif
    if lower(right(cBase,4))==".emf"
        cBase := left(cBase,len(cBase)-4)
    endif
    GetFonts()
    cPDF := StrTran(StrTran(cBase,"*",""),"?","")+".pdf"
    aFiles := Directory(cBase+".emf")
    if len(aFiles)=0
        ? "File not found"
        return -1
    endif
return IIF(CreatePDF(cPdf,aFiles),0,-2)

func CreatePDF(cPdf, aMetas)
    LOCAL hDC, pdf, f, hMeta
    hDC := CreateDC( "DISPLAY",0,0,0)
    pdf := HPDF_New()
    HPDF_SetCompressionMode( pdf, HPDF_COMP_ALL )
    if file(cPDF)
        fErase(cPDF)
    endif
    for each f in aMetas
        hMeta := GetEnhMetaFile(f[1])
        EnumEnhMetaFile(hDC,hMeta,{|pDC,pTable,pRECORD| MyCB(pdf,pTable,pRECORD) },{0,0,100,100})
    next
    HPDF_SaveToFile( pdf, cPDF )
return HPDF_GetError( pdf )=0

  
static func MyCB(pdf,pTable,pRECORD)
    LOCAL page := pTable[1]
    if len(aCreated)<>len(pTable)
        aSize(aCreated,len(pTable))
    endif
    switch pRecord[1]
        CASE 1 // EMT_HEADER
            pdf_Header(pdf,pRecord,@pTable)
            exit            
        case 24 // EMR_SETTEXTCOLOR
            pdf_SetTextColor(page,pRecord)
            exit            
        case 27 // EMR_MOVETOEX
            pdf_MoveTo(page,pRecord)
            exit
        case 37 // EMR_SELECTOBJECT
            PDF_SelectObject(page,pTable,pRecord)
            exit
        case 38 // EMR_CREATEPEN
            pdf_CreatePen(pRecord)
            exit
        case 39 // EMR_CREATEBRUSHINDIRECT
            pdf_CreateBrush(pRecord)
            exit
        case 54 // EMR_LINETO
            pdf_LineTo(page,pRecord)
            exit
        case 76 // EMR_BITBLT
            pdf_BitBlt(page,pRecord)
            exit
        case 82 // EMR_EXTCREATEFONTINDIRECTW
            pdf_CreateFont(pdf,page,pTable,pRecord)
            exit
        case 84 //EMR_EXTTEXTOUTW
            pdf_TextOut(page,pRecord)
            exit
    endswitch
return 1

static proc pdf_Header(pdf,pRecord,pTable)
    page := HPDF_AddPage( pdf )
    //The dimensions are in 100ths of millimeter, must be 72ths of inch
    // v/100 -> millimeter
    // v/100/25.4 --> inch
    // v/2540*72 --> 72ths of inch
    // v*72/2540 --> 72ths of inch
    // v*18/635 --> 72ths of inch
    HPDF_Page_SetWidth(page,pRecord[8]*18/635)
    HPDF_Page_SetHeight(page,pRecord[9]*18/635)
    xScale := (pRecord[8]*18)/(635 * pRecord[18])
    yScale := (pRecord[9]*18)/(635 * pRecord[19])
    pTable[1] := page
    HPDF_Page_SetFontAndSize( page, HPDF_GetFont( pdf, "Helvetica", NIL ), 12 )
return

static proc pdf_SetTextColor(page,pRecord)
    LOCAL r := hb_bitAnd(hb_bitShift(pRecord[2],- 0),0xFF)/255
    LOCAL g := hb_bitAnd(hb_bitShift(pRecord[2],- 8),0xFF)/255
    LOCAL b := hb_bitAnd(hb_bitShift(pRecord[2],-16),0xFF)/255
    HPDF_Page_SetRGBFill(page, r,g,b)
    HPDF_Page_SetRGBStroke(page, r,g,b)
return

static proc pdf_MoveTo(page,pRecord)
    currX := pRecord[2]*xScale
    currY := HPDF_Page_GetHeight( page )-pRecord[3]*yScale
    //HPDF_Page_MoveTo(page,currX, currY)
return

static proc pdf_LineTo(page,pRecord)
    HPDF_Page_MoveTo(page,currX, currY)
    currX := pRecord[2]*xScale
    currY := HPDF_Page_GetHeight( page )-pRecord[3]*yScale
    HPDF_Page_LineTo(page,currX, currY)
    HPDF_Page_Stroke(page)
return

static proc pdf_CreatePen(pRecord)
    // warning:  pRecord[3] is style, ignore
    aCreated[pRecord[2]+1] := {"pen", pRecord[4]*xScale, ;
        hb_bitAnd(hb_bitShift(pRecord[6],-0),0xFF)/255, ;
        hb_bitAnd(hb_bitShift(pRecord[6],-8),0xFF)/255, ;
        hb_bitAnd(hb_bitShift(pRecord[6],-16),0xFF)/255}
return

static proc pdf_CreateBrush(pRecord)
    // warning:  pRecord[3] is style, ignore
    aCreated[pRecord[2]+1] := {"brush", ;
        hb_bitAnd(hb_bitShift(pRecord[4],-0),0xFF)/255, ;
        hb_bitAnd(hb_bitShift(pRecord[4],-8),0xFF)/255, ;
        hb_bitAnd(hb_bitShift(pRecord[4],-16),0xFF)/255}
return

static func ReadW(aRecord,nStart,nLen)
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

static proc pdf_TextOut(page,pRecord)
    LOCAL cTxt := ReadW(pRecord,19,pRecord[11]), h := HPDF_Page_GetHeight( page ), dbg
    LOCAL nItalic, fontSize := HPDF_Page_GetCurrentFontSize(page), startDX := pRecord[18]/4
    LOCAL endW := 0xFFFFFFFF,x,y0,y1
    if currFont[2]
        // bold
        HPDF_Page_SetTextRenderingMode(page,HPDF_FILL_THEN_STROKE)
        HPDF_Page_SetLineWidth(page,HPDF_Page_GetCurrentFontSize(page)/20)
    endif
    HPDF_Page_BeginText( page )
    if currFont[1]<=0 .or. currFont[1]>1
        currFont[1]:=1
    endif
    nItalic := iif(currFont[3],0.333,0)
    HPDF_Page_SetTextMatrix(page, currFont[1], 0,currFont[1]*nItalic,1, 0, 0)
    if hb_bitAnd(pRecord[13],4)>0
        endW := pRecord[16]*xScale
    endif
    x := pRecord[9]*xScale
    y0 := h-pRecord[5]*yScale+fontSize
    y1 :=  h-pRecord[3]*yScale+fontSize
    //y := h-pRecord[10]*yScale//-fontSize
    //y :=  h-pRecord[3]*yScale+fontSize
    for i:=1 to len(cTxt)
        HPDF_Page_TextRect( page, x, y0, x+2*pRecord[startDX+i-1]*xScale/currFont[1], y1, substr(cTxt,i,1),0)
        //HPDF_Page_TextOut(page,x,y,substr(cTxt,i,1))
        x+=pRecord[startDX+i-1]*xScale
        if x>endW
            exit
        endif
    next
    //HPDF_Page_TextRect( page, pRecord[2]*xScale, h-pRecord[5]*yScale+fontSize, (pRecord[2]+(pRecord[4]-pRecord[2])/currFont[1])*xScale, h-pRecord[3]*yScale+fontSize, cTXT,0)
    HPDF_Page_EndText( page )
    HPDF_Page_SetTextRenderingMode(page,HPDF_FILL)

return

static proc pdf_BitBlt(page,pRecord)
    // always do a filled rectangle
    LOCAL h := HPDF_Page_GetHeight( page )
    HPDF_Page_Rectangle(page,pRecord[2]*xScale,h-pRecord[5]*yScale, ;
        (pRecord[4]-pRecord[2])*xScale, (pRecord[5]-pRecord[3])*yScale)
    HPDF_Page_Fill(page)
return

static proc PDF_SelectObject(page,pTable,pRecord)
    if pRecord[2]<len(pTable)
        if !empty(aCreated[pRecord[2]+1]) 
            if aCreated[pRecord[2]+1,1] == "font"
                HPDF_Page_SetFontAndSize( page, pTable[pRecord[2]+1], aCreated[pRecord[2]+1,2] )
                currFont := {aCreated[pRecord[2]+1,3],aCreated[pRecord[2]+1,4],aCreated[pRecord[2]+1,5]}
            elseif aCreated[pRecord[2]+1,1] == "pen"
                HPDF_Page_SetLineWidth(page,aCreated[pRecord[2]+1,2])
                HPDF_Page_SetRGBStroke(page,aCreated[pRecord[2]+1,3],aCreated[pRecord[2]+1,4],aCreated[pRecord[2]+1,5])
            elseif aCreated[pRecord[2]+1,1] == "brush"
                HPDF_Page_SetRGBFill(page,aCreated[pRecord[2]+1,2],aCreated[pRecord[2]+1,3],aCreated[pRecord[2]+1,4])
            endif
            return
        endif
        return
    endif
    if pRecord[2]<0x80000000
        return
    endif
    switch hb_bitAnd(pRecord[2],0xFF)
    case 0x00 //WHITE_BRUSH
        HPDF_Page_SetRGBFill(page,1,1,1)
        exit
    case 0x01 //LTGRAY_BRUSH
        HPDF_Page_SetRGBFill(page,0.75,0.75,0.75)
        exit
    case 0x02 //GRAY_BRUSH
        HPDF_Page_SetRGBFill(page,0.5,0.5,0.5)
        exit
    case 0x03 // DKGRAY_BRUSH
        HPDF_Page_SetRGBFill(page,0.25,0.25,0.25)
        exit
    case 0x04 //BLACK_BRUSH
        HPDF_Page_SetRGBFill(page,0,0,0)
        exit
    case 0x05 //NULL_BRUSH
        exit
    case 0x06 //WHITE_PEN
        HPDF_Page_SetLineWidth(page,1)
        HPDF_Page_SetRGBStroke(page,1,1,1)
        exit
    case 0x07 //BLACK_PEN
        HPDF_Page_SetLineWidth(page,1)
        HPDF_Page_SetRGBStroke(page,0,0,0)
        exit
    case 0x08 //NULL_PEN"
        exit
    case 0x0A //OEM_FIXED_FONT"
        exit
    case 0x0B // ANSI_FIXED_FONT"
        exit
    case 0x0C // ANSI_VAR_FONT"
        exit
    case 0x0D // SYSTEM_FONT"
        exit
    case 0x0E // DEVICE_DEFAULT_FONT"
        exit
    case 0x0F // DEFAULT_PALETTE"
        exit
    case 0x10 // SYSTEM_FIXED_FONT"
        exit
    case 0x11 // DEFAULT_GUI_FONT"
        exit
    case 0x12 // DC_BRUSH"
        exit
    case 0x13// DC_PEN"
        exit
    endswitch
return

static func Ckfont(xVal,cFontName,lBold,lItalic)
    if !cFontName $ xVal
        return .F.
    endif
    if lBold .and. !"bold" $ xVal
        return .F.
    endif
    if lItalic .and. !"italic" $ xVal
        return .F.
    endif
return .T.

static proc pdf_CreateFont(pdf,page,pTable,pRecord)
    local cInFile := lower(ReadW(pRecord,10,32))
    LOCAL i, h, w
    LOCAL cPDF, lBold, lItalic, lRealBold, lRealItalic
    lRealBold   := lBold   := pRecord[7]>550
    lRealItalic := lItalic := hb_bitShift(hb_bitAnd(pRecord[8],0x0FF),0)>0
    i:= aScan(fontList,{|x| CkFont(x[1],cInFile,lBold,lItalic)})
    if i==0 .and. lBold .and. lItalic
        i := aScan(fontList,{|x| CkFont(x[1],cInFile,.T.,.F.)})        
        if i>0
            lRealItalic := .F.
        else
            i := aScan(fontList,{|x| CkFont(x[1],cInFile,.F.,.T.)})
            if i>0
                lRealBold := .F.
            else
                i := aScan(fontList,{|x| CkFont(x[1],cInFile,.F.,.F.)})
                lRealBold := lRealItalic := .F.
            endif
        endif
    elseif i==0 .and. (lBold .or. lItalic)
        i:=aScan(fontList,{|x| CkFont(x[1],cInFile,.F.,.F.)})
        lRealBold := lRealItalic := .F.
    endif
    if i>0
        cPDF := HPDF_LoadTTFontFromFile(pdf, fontList[i,2])
        pTable[pRecord[2]+1]:=HPDF_GetFont( pdf, cPDF, NIL )
        h =  pRecord[3]
        if h>0x8000000
            h:=0xFFFFFFFF-pRecord[3]+1
        endif
        HPDF_Page_SetFontAndSize( page, pTable[pRecord[2]+1], h*yScale )
        i := HPDF_Font_GetBBox(pTable[pRecord[2]+1])
        w := (i[3]-i[1])*h/(i[2]-i[4])
        if lBold 
            lBold := !lRealBold
            // se RealBold è true, il font è già grassetto e non deve essere fatto
            // se RealBold è false, il font è da grassettare
        endif
        if lItalic 
            lItalic := !lRealItalic
            // se lRealItalic è true, il font è già corsivo e non deve essere fatto
            // se lRealItalic è false, il font è da inclinare
        endif
        aCreated[pRecord[2]+1] := {"font",h*yScale, pRecord[4]/w,lBold,lItalic }
    endif
return

static proc GetFonts()
    #define  HKEY_LOCAL_MACHINE      0x80000002
    LOCAL oReg
    LOCAL cKey, cValue
    LOCAL nId := 1
    if !empty(fontList)
        return
    endif
    oReg := TReg32():New(HKEY_LOCAL_MACHINE, "Software\Microsoft\Windows NT\CurrentVersion\Fonts", .t.)
    fontList := {}

    //? oReg:nError
    do while .t.
       oReg:nError := MY_REGENUMVALUE(oReg:nHandle, nId, @cKey, @cValue)
       cValue := GETWINDOWSDIRECTORY()+"\fonts\"+cValue
       aadd(fontList, {lower(cKey), cValue })
       if oReg:nError<>0
          exit
       endif
       nId += 1         
    enddo
    //XBROWSER fontList
return

#pragma begindump
#include <windows.h>
#include <hbapi.h>
#include <hbapiitm.h>
#include <hbstack.h>

#ifndef _WIN64
#define hb_parfw hb_parnl
#define hb_itempPutFw hb_itemPutNL
#define FWCAST long
#else
#define hb_parfw hb_parnll
#define hb_itempPutFw hb_itemPutNLL
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
        hb_itemArrayPut(pHandleTable,i+1,hb_itemPutPtr(0,lpHTable->objectHandle[i]));
        
    hb_itemArrayPut(pRecord,1,hb_itemPutNI(0,lpEMFR->iType));
    for(i=0;i<(int)lpEMFR->nSize/4;i++)
        hb_itemArrayPut(pRecord,i+2,hb_itemPutNInt(0,lpEMFR->dParm[i]));

    hb_evalBlock(pBlock, pDC, pHandleTable, pRecord, 0);

    for(i=0;i<nObj;i++)
        lpHTable->objectHandle[i] = (HGDIOBJ)hb_itemGetPtr(hb_itemArrayGet(pHandleTable,i+1));

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

HB_FUNC( MY_REGENUMVALUE ) // ( nKey, nIndex, @cKeyName, @uValue ) --> nResult
{
   BYTE name[ 1024 ];
   BYTE value[ 1024 ];
   DWORD lName=1024, lValue=1024, type = 0;
 
   hb_retnl( RegEnumValueA( ( HKEY ) hb_parfw( 1 ), hb_parnl( 2 ), ( LPSTR ) name, &lName, 0, &type, value, &lValue ) );
   hb_storc( ( const char * ) name, 3 );
 
   switch( type )
   {
      case REG_SZ:
            hb_storc( ( const char * ) value, 4 );
           break;
 
      case REG_DWORD:
           hb_stornl( * ( ( LPDWORD ) value ), 4 );
           break;      
   }
}

#pragma enddump
