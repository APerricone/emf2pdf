SET CD_SRC=%CD%
CALL "c:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
set HB_INSTALL=C:\harbour32
SET PATH=%PATH%;C:\harbour32\bin\win\msvc
CD %CD_SRC%
echo on 

hbmk2 emf2pdf.prg emf2pdf.hbp -oemf2pdf
hbmk2 emf2txt.prg emf2pdf.hbp -oemf2txt

hbmk2 dbglib.prg emf2pdf.prg emf2pdf.hbp -b -oemf2pdf_dbg -workdir=OBJ_dbg
hbmk2 dbglib.prg emf2txt.prg emf2pdf.hbp -b -oemf2txt_dbg -workdir=OBJ_dbg

