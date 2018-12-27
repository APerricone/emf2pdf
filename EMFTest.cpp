// EMFTest.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"

const char* emfNames[] = {
	"EMR_HEADER", /*1*/
	"EMR_POLYBEZIER", /*2*/
	"EMR_POLYGON", /*3*/
	"EMR_POLYLINE", /*4*/
	"EMR_POLYBEZIERTO", /*5*/
	"EMR_POLYLINETO", /*6*/
	"EMR_POLYPOLYLINE", /*7*/
	"EMR_POLYPOLYGON", /*8*/
	"EMR_SETWINDOWEXTEX", /*9*/
	"EMR_SETWINDOWORGEX", /*10*/
	"EMR_SETVIEWPORTEXTEX", /*11*/
	"EMR_SETVIEWPORTORGEX", /*12*/
	"EMR_SETBRUSHORGEX", /*13*/
	"EMR_EOF", /*14*/
	"EMR_SETPIXELV", /*15*/
	"EMR_SETMAPPERFLAGS", /*16*/
	"EMR_SETMAPMODE", /*17*/
	"EMR_SETBKMODE", /*18*/
	"EMR_SETPOLYFILLMODE", /*19*/
	"EMR_SETROP2", /*20*/
	"EMR_SETSTRETCHBLTMODE", /*21*/
	"EMR_SETTEXTALIGN", /*22*/
	"EMR_SETCOLORADJUSTMENT", /*23*/
	"EMR_SETTEXTCOLOR", /*24*/
	"EMR_SETBKCOLOR", /*25*/
	"EMR_OFFSETCLIPRGN", /*26*/
	"EMR_MOVETOEX", /*27*/
	"EMR_SETMETARGN", /*28*/
	"EMR_EXCLUDECLIPRECT", /*29*/
	"EMR_INTERSECTCLIPRECT", /*30*/
	"EMR_SCALEVIEWPORTEXTEX", /*31*/
	"EMR_SCALEWINDOWEXTEX", /*32*/
	"EMR_SAVEDC", /*33*/
	"EMR_RESTOREDC", /*34*/
	"EMR_SETWORLDTRANSFORM", /*35*/
	"EMR_MODIFYWORLDTRANSFORM", /*36*/
	"EMR_SELECTOBJECT", /*37*/
	"EMR_CREATEPEN", /*38*/
	"EMR_CREATEBRUSHINDIRECT", /*39*/
	"EMR_DELETEOBJECT", /*40*/
	"EMR_ANGLEARC", /*41*/
	"EMR_ELLIPSE", /*42*/
	"EMR_RECTANGLE", /*43*/
	"EMR_ROUNDRECT", /*44*/
	"EMR_ARC", /*45*/
	"EMR_CHORD", /*46*/
	"EMR_PIE", /*47*/
	"EMR_SELECTPALETTE", /*48*/
	"EMR_CREATEPALETTE", /*49*/
	"EMR_SETPALETTEENTRIES", /*50*/
	"EMR_RESIZEPALETTE", /*51*/
	"EMR_REALIZEPALETTE", /*52*/
	"EMR_EXTFLOODFILL", /*53*/
	"EMR_LINETO", /*54*/
	"EMR_ARCTO", /*55*/
	"EMR_POLYDRAW", /*56*/
	"EMR_SETARCDIRECTION", /*57*/
	"EMR_SETMITERLIMIT", /*58*/
	"EMR_BEGINPATH", /*59*/
	"EMR_ENDPATH", /*60*/
	"EMR_CLOSEFIGURE", /*61*/
	"EMR_FILLPATH", /*62*/
	"EMR_STROKEANDFILLPATH", /*63*/
	"EMR_STROKEPATH", /*64*/
	"EMR_FLATTENPATH", /*65*/
	"EMR_WIDENPATH", /*66*/
	"EMR_SELECTCLIPPATH", /*67*/
	"EMR_ABORTPATH", /*68*/
	"RESERVED_69",/*69*/
	"EMR_GDICOMMENT", /*70*/
	"EMR_FILLRGN", /*71*/
	"EMR_FRAMERGN", /*72*/
	"EMR_INVERTRGN", /*73*/
	"EMR_PAINTRGN", /*74*/
	"EMR_EXTSELECTCLIPRGN", /*75*/
	"EMR_BITBLT", /*76*/
	"EMR_STRETCHBLT", /*77*/
	"EMR_MASKBLT", /*78*/
	"EMR_PLGBLT", /*79*/
	"EMR_SETDIBITSTODEVICE", /*80*/
	"EMR_STRETCHDIBITS", /*81*/
	"EMR_EXTCREATEFONTINDIRECTW", /*82*/
	"EMR_EXTTEXTOUTA", /*83*/
	"EMR_EXTTEXTOUTW", /*84*/
	"EMR_POLYBEZIER16", /*85*/
	"EMR_POLYGON16", /*86*/
	"EMR_POLYLINE16", /*87*/
	"EMR_POLYBEZIERTO16", /*88*/
	"EMR_POLYLINETO16", /*89*/
	"EMR_POLYPOLYLINE16", /*90*/
	"EMR_POLYPOLYGON16", /*91*/
	"EMR_POLYDRAW16", /*92*/
	"EMR_CREATEMONOBRUSH", /*93*/
	"EMR_CREATEDIBPATTERNBRUSHPT", /*94*/
	"EMR_EXTCREATEPEN", /*95*/
	"EMR_POLYTEXTOUTA", /*96*/
	"EMR_POLYTEXTOUTW", /*97*/

#if(WINVER >= 0x0400)
	"EMR_SETICMMODE", /*98*/
	"EMR_CREATECOLORSPACE", /*99*/
	"EMR_SETCOLORSPACE", /*100*/
	"EMR_DELETECOLORSPACE", /*101*/
	"EMR_GLSRECORD", /*102*/
	"EMR_GLSBOUNDEDRECORD", /*103*/
	"EMR_PIXELFORMAT", /*104*/
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
	"EMR_RESERVED_105", /*105*/
	"EMR_RESERVED_106", /*106*/
	"EMR_RESERVED_107", /*107*/
	"EMR_RESERVED_108", /*108*/
	"EMR_RESERVED_109", /*109*/
	"EMR_RESERVED_110", /*110*/
	"EMR_COLORCORRECTPALETTE", /*111*/
	"EMR_SETICMPROFILEA", /*112*/
	"EMR_SETICMPROFILEW", /*113*/
	"EMR_ALPHABLEND", /*114*/
	"EMR_SETLAYOUT", /*115*/
	"EMR_TRANSPARENTBLT", /*116*/
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
	"EMR_RESERVED_117", /*117*/
#endif // (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
	"EMR_GRADIENTFILL", /*118*/
	"EMR_RESERVED_119", /*119*/
	"EMR_RESERVED_120", /*120*/
	"EMR_COLORMATCHTOTARGETW", /*121*/
	"EMR_CREATECOLORSPACEW", /*122*/
#endif
	"END"
};

struct emf2PdfFont
{
	HPDF_Font font;
	float height, width;
	bool fakeBold;
	bool fakeItalic;
};

struct emf2PdfPen
{
	float width,r,g,b;
};

struct emf2PdfBrush
{
	bool solid;
	float r, g, b;
};

struct emf2PdfData
{
	HPDF_Doc pdf;
	HPDF_Page page;
	float currHeight;
	float xScale, yScale,scale;
	struct
	{
		int id;
		int type;
		union
		{
			emf2PdfFont font;
			emf2PdfPen pen;
			emf2PdfBrush brush;
		};
	} *created;
	float currX, currY;
	bool inPath;
	float pathStartX, pathStartY;
	emf2PdfFont currentFont;
	emf2PdfPen currentPen;
	emf2PdfBrush currentBrush;
} e2pd;

void InitEMF2PDF(emf2PdfData &d, HPDF_Doc pdf)
{
	d.pdf = pdf;
	d.page = HPDF_AddPage(pdf);
	d.xScale = d.yScale = d.scale = 0;
	d.inPath = false;
	d.created = 0;
	d.currX = d.currY = 0;
	d.currentFont.font = HPDF_GetFont(pdf, "Helvetica", 0);
	d.currentFont.height = 14;
	d.currentFont.width = 0;
	d.currentFont.fakeBold = d.currentFont.fakeItalic = false;
	d.currentPen.r = d.currentPen.g = d.currentPen.b = 0.f;
	d.currentBrush.solid = true;
	d.currentBrush.r = d.currentBrush.g = d.currentBrush.b = 0.f;
}

size_t EMF2PDF_Header(FILE *f,HPDF_Doc pdf)
{
	size_t nRead = 0;
	RECTL frame;
	fread(&frame, sizeof(RECTL), 1, f); //bounds
	fread(&frame, sizeof(RECTL), 1, f); // frame
	printf("  Page size %ix%i (%ix%i)\r\n", frame.right, frame.bottom, frame.left, frame.top);
	InitEMF2PDF(e2pd, pdf);
	HPDF_Page_SetWidth(e2pd.page, (HPDF_REAL)(frame.right * 18. / 635.));
	HPDF_Page_SetHeight(e2pd.page, (HPDF_REAL)(frame.bottom * 18. / 635.));
	nRead += sizeof(RECTL) * 2;
	fseek(f, 40, SEEK_CUR);
	SIZEL mm;
	fread(&mm, sizeof(SIZEL), 1, f); // frame
	printf("  mm %ix%i\r\n", mm.cx,mm.cy);
	e2pd.xScale = (frame.right * 18.f) / (635.f * mm.cx);
	e2pd.yScale = (frame.bottom * 18.f) / (635.f * mm.cy);
	e2pd.scale = e2pd.xScale > e2pd.yScale ? e2pd.xScale : e2pd.yScale;
	nRead += 40+sizeof(SIZEL);
	e2pd.currHeight = HPDF_Page_GetHeight(e2pd.page);
	return nRead;
}

size_t EMF2PDF_MoveToEx(FILE *f)
{
	POINTL p;
	fread(&p, sizeof(POINTL), 1, f); // pos
	e2pd.currX = p.x * e2pd.xScale;
	e2pd.currY = e2pd.currHeight - p.y * e2pd.yScale;
	e2pd.pathStartX = e2pd.currX;
	e2pd.pathStartY = e2pd.currY;
	printf("  move to %i,%i\r\n", p.x, p.y);
	HPDF_Page_MoveTo(e2pd.page, e2pd.currX, e2pd.currY);
	return sizeof(POINTL);
}

size_t EMF2PDF_LineTo(FILE *f)
{
	POINTL p;
	fread(&p, sizeof(POINTL), 1, f); // pos
	e2pd.currX = p.x * e2pd.xScale;
	e2pd.currY = e2pd.currHeight - p.y * e2pd.yScale;
	printf("  move to %i,%i\r\n", p.x, p.y);
	HPDF_Page_LineTo(e2pd.page, e2pd.currX, e2pd.currY);
	if (!e2pd.inPath) HPDF_Page_Stroke(e2pd.page);
	return sizeof(POINTL);
}


size_t EMF2PDF_SelectObject(FILE *f)
{
	unsigned long obj;
	fread(&obj, 4, 1, f);
	if(obj>=0x80000000) {
		printf(" Obj 0x%8X\r\n", obj);
		switch (obj & 0xFF)
		{
		case WHITE_BRUSH:
			e2pd.currentBrush.solid = true;
			e2pd.currentBrush.r = e2pd.currentBrush.g = e2pd.currentBrush.b = 1.f;
			HPDF_Page_SetRGBFill(e2pd.page, e2pd.currentBrush.r, e2pd.currentBrush.g, e2pd.currentBrush.b);
			break;
		case LTGRAY_BRUSH:
			e2pd.currentBrush.solid = true;
			e2pd.currentBrush.r = e2pd.currentBrush.g = e2pd.currentBrush.b = 0.75f;
			HPDF_Page_SetRGBFill(e2pd.page, e2pd.currentBrush.r, e2pd.currentBrush.g, e2pd.currentBrush.b);
			break;
		case GRAY_BRUSH:
			e2pd.currentBrush.solid = true;
			e2pd.currentBrush.r = e2pd.currentBrush.g = e2pd.currentBrush.b = 0.5f;
			HPDF_Page_SetRGBFill(e2pd.page, e2pd.currentBrush.r, e2pd.currentBrush.g, e2pd.currentBrush.b);
			break;
		case DKGRAY_BRUSH:
			e2pd.currentBrush.solid = true;
			e2pd.currentBrush.r = e2pd.currentBrush.g = e2pd.currentBrush.b = 0.25f;
			HPDF_Page_SetRGBFill(e2pd.page, e2pd.currentBrush.r, e2pd.currentBrush.g, e2pd.currentBrush.b);
			break;
		case BLACK_BRUSH:
			e2pd.currentBrush.solid = true;
			e2pd.currentBrush.r = e2pd.currentBrush.g = e2pd.currentBrush.b = 0.f;
			HPDF_Page_SetRGBFill(e2pd.page, e2pd.currentBrush.r, e2pd.currentBrush.g, e2pd.currentBrush.b);
			break;
		case NULL_BRUSH:
			e2pd.currentBrush.solid = false;
			break;
		case WHITE_PEN:
			e2pd.currentPen.width = 1;
			e2pd.currentPen.r = e2pd.currentPen.g = e2pd.currentPen.b = 1.f;
			HPDF_Page_SetLineWidth(e2pd.page, e2pd.currentPen.width*e2pd.scale);
			HPDF_Page_SetRGBStroke(e2pd.page, e2pd.currentPen.r, e2pd.currentPen.g, e2pd.currentPen.b);
			break;
		case BLACK_PEN:
			e2pd.currentPen.width = 1;
			e2pd.currentPen.r = e2pd.currentPen.g = e2pd.currentPen.b = 0.f;
			HPDF_Page_SetLineWidth(e2pd.page, e2pd.currentPen.width*e2pd.scale);
			HPDF_Page_SetRGBStroke(e2pd.page, e2pd.currentPen.r, e2pd.currentPen.g, e2pd.currentPen.b);
			break;
		case NULL_PEN:
			e2pd.currentPen.width = 0;
			e2pd.currentPen.r = e2pd.currentPen.g = e2pd.currentPen.b = 0.f;
			break;
		case OEM_FIXED_FONT:
		case ANSI_FIXED_FONT:
		case ANSI_VAR_FONT:
		case SYSTEM_FONT:
		case DEVICE_DEFAULT_FONT:
		case DEFAULT_PALETTE:
		case SYSTEM_FIXED_FONT:
		case DEFAULT_GUI_FONT:
		case DC_BRUSH:
		case DC_PEN:
			//TODO
			break;
		}
	} else {
		printf(" Obj %i\r\n", obj);
	}
	return 4;
}

void AddEMF2PDF(HPDF_Doc pdf, FILE *f)
{
	while (!feof(f))
	{
		unsigned long code, size;
		size_t r = fread(&code, sizeof(unsigned long), 1, f);
		if (r < 1) break;
		r = fread(&size, sizeof(unsigned long), 1, f);
		if (r < 1) break;
		size_t nRead = 8;
		printf("Record %i(%s) length %i\r\n", code, emfNames[code - 1], size);
		switch (code)
		{
		case EMR_HEADER:		nRead += EMF2PDF_Header(f, pdf); break;
		case EMR_MOVETOEX:		nRead += EMF2PDF_MoveToEx(f); break;
		case EMR_SELECTOBJECT:	nRead += EMF2PDF_SelectObject(f); break;
		case EMR_LINETO:		nRead += EMF2PDF_LineTo(f); break;
		//case EMR_BEGINPATH:		nRead += EMF2PDF_BeginPath(f); break;
		}
		fseek(f, size - nRead, SEEK_CUR);
	}
}

int main(int argc, const char* argv[])
{
	const char *fileToOpen = "eofill.emf";
	if (argc > 1) fileToOpen = argv[1];
#ifdef WIN32
	FILE *f;
	errno_t err = fopen_s(&f, fileToOpen, "rb");
	if (err > 0)
	{
		printf("Error file %s - %i", fileToOpen, err);
		return -1;
	}
#else
	FILE *f = fopen(fileToOpen, "rb");
#endif
	HPDF_Doc pdf = HPDF_New(0, 0);
	if (!f)
	{
		printf("File not found %s", fileToOpen);
		return -1;
	}
	AddEMF2PDF(pdf, f);
	fclose(f);
	int l = strlen(fileToOpen);
	char *fileToSave = (char*)malloc(l + 2);
	strcpy_s(fileToSave, l + 2, fileToOpen);
	char *extension = strrchr(fileToSave, (int)'.');
	strcpy_s(extension, 5, ".pdf");
	HPDF_SaveToFile(pdf, fileToSave);
}
