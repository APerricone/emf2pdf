
// Example of interface with FiveWin http://www.fivetechsoft.com/english/
// it uses hbhpdf + Emf2Pdf to convert the preview of a TPrinter into PDF
PROC TPrinter2PDF(oPrn, cFile)
   LOCAL i, oPdf := HPDF_New()
   for i:=1 to len(oPrn:aMeta)
      HPDF_ADDEMF(oPdf, oPrn:aMeta[i])
   next
   HPDF_SaveToFile( oPdf, cFile)
return

