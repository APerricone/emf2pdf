#include "fivewin.ch"

function Main()

   local oPrn, oFont, nCh
   local oBrushRed, oBrushGreen

   //nCh   := Alert( "Create PDF using", { "FWH", "WORD", "IMG2PDF" } )
   //if nCh == 0
   //   return nil
   //elseif nCh == 1
   //   TPreview():bSaveAsPDF := { |o| FWSavePreviewToPDF( o:oDevice ) }
   //elseif nCh == 3
   //   TPreview():bSaveAsPDF := { |o| Image2PDF( o:oDevice:aMeta ) }
   //endif
   TPreview():bSaveAsPDF := {|o| TPrinter2PDF(o:oDevice)}
   PRINT oPrn PREVIEW

   DEFINE FONT oFont NAME "TAHOMA" SIZE 0,-20 OF oPrn
   DEFINE BRUSH oBrushRed    COLOR CLR_HRED
   DEFINE BRUSH oBrushGreen  COLOR CLR_HGREEN

   PAGE

      @  300,100 PRINT TO oPrn TEXT "YELLOW ON RED"   SIZE 2000,200 PIXEL FONT oFont COLOR CLR_YELLOW,oBrushRed
      @  620,100 PRINT TO oPrn TEXT "DEFAULT COLORS"  SIZE 2000,200 PIXEL FONT oFont
      @  940,100 PRINT TO oPrn TEXT "BLUE ON GREEN"   SIZE 2000,200 PIXEL FONT oFont COLOR CLR_BLUE,  oBrushGreen
      @ 1260,100 PRINT TO oPrn TEXT "DEFAULT COLORS"  SIZE 2000,200 PIXEL FONT oFont
      @ 1580,100 PRINT TO oPrn TEXT "YELLOW ON RED"   SIZE 2000,200 PIXEL FONT oFont COLOR CLR_YELLOW,oBrushRed

      SetBkColor( oPrn:hDCOut, CLR_HRED )
      oPrn:Say(  300, 2600, "YELLOW ON RED", oFont, 2000, CLR_YELLOW, 2 )
      SetBkColor( oPrn:hDCOut, CLR_HGREEN )
      oPrn:Say(  940, 2600, "BLUE ON GREEN", oFont, 2000, CLR_BLUE,   2 )


   ENDPAGE
   ENDPRINT

   RELEASE FONT oFont
   RELEASE BRUSH oBrushRed, oBrushGreen

return nil

PROC TPrinter2PDF(oPrn, cFile)
   LOCAL i, oPdf := HPDF_New()
   DEFAULT cFile := cGetFile( "(*.pdf)|*.pdf|", "Select PDF File to Save",, CurDir(), .T. )
   if !empty(oPrn:aMeta)
      ? oPrn:aMeta[1]
   endif
   for i:=1 to len(oPrn:aMeta)
      HPDF_ADDEMF(oPdf, oPrn:aMeta[i])
   next
   HPDF_SaveToFile( oPdf, cFile)
return
