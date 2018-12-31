// EMFTest.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"

#define _CONSOLE_DEBUG
#if defined(_CONSOLE_DEBUG)
#define PRINT_DBG printf
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
#else
#define PRINT_DBG 
#endif

class Emf2Pdf
{
public:

	Emf2Pdf(HPDF_Doc pdf);
	~Emf2Pdf();

	bool AddEMF(const char* cFileName);

private:
	struct SystemFont
	{
		const char* name;
		const char* path;
	};
	static SystemFont* installedFont;
	static void InitInstalledFont();

	struct Font
	{
		HPDF_Font font;
		float height, width;
		bool fakeBold;
		bool fakeItalic;
	};

	struct Pen
	{
		float width, r, g, b;
	};

	struct Brush
	{
		bool solid;
		float r, g, b;
	};

	struct CreatedItem
	{
		int id;
		int type;
		union
		{
			Font font;
			Pen pen;
			Brush brush;
		};
	};

	HPDF_Doc pdf;
	HPDF_Page page;
	float currHeight;
	float xScale, yScale, scale;
	unsigned int nCreated;
	CreatedItem* created;
	float currX, currY;
	bool inPath;
	float pathStartX, pathStartY;
	Font currentFont;
	Pen currentPen;
	Brush currentBrush;
	float rText, gText, bText;
	FILE *f;
	boolean polyEO;

	void Reset();
	void SetCreatedIdx(unsigned long idx);

	size_t Header();
	size_t MoveToEx();
	size_t LineTo();
	size_t PolyBezier(unsigned long code);
	size_t SelectObject();
	size_t SetTextColor();
	size_t CreatePen();
	size_t CreateBrush();
	size_t BeginPath();
	size_t CloseFigure();
	size_t EndPath();
	size_t FillPath();
	size_t SelectClipPath();
	size_t SetPolyFillMode();

	void ParseFile();
};

Emf2Pdf::Emf2Pdf(HPDF_Doc pdf)
{
	this->pdf = pdf;
	nCreated = 0;
	created = 0;
	Reset();
}

void Emf2Pdf::Reset()
{
	xScale = yScale = scale = 0;
	inPath = false;
	if (created != 0)
	{
		free(created);
	}
	created = 0;
	currX = currY = 0;
	currentFont.font = HPDF_GetFont(pdf, "Helvetica", 0);
	currentFont.height = 14;
	currentFont.width = 0;
	currentFont.fakeBold = currentFont.fakeItalic = false;
	currentPen.r = currentPen.g = currentPen.b = 0.f;
	currentBrush.solid = true;
	currentBrush.r = currentBrush.g = currentBrush.b = 0.f;
	polyEO = false;
}

Emf2Pdf::~Emf2Pdf()
{
	Reset();
}

size_t Emf2Pdf::Header()
{
	size_t nRead = 0;
	RECTL frame;
	fread(&frame, sizeof(RECTL), 1, f); //bounds
	fread(&frame, sizeof(RECTL), 1, f); // frame
	PRINT_DBG("  Page size %ix%i (%ix%i)\r\n", frame.right, frame.bottom, frame.left, frame.top);
	page = HPDF_AddPage(pdf);
	//The dimensions are in 100ths of millimeter, must be 72ths of inch
	// v/100 -> millimeter
	// v/100/25.4 --> inch
	// v/2540*72 --> 72ths of inch
	// v*72/2540 --> 72ths of inch
	// v*18/635 --> 72ths of inch
	HPDF_Page_SetWidth(page, (HPDF_REAL)(frame.right * 18. / 635.));
	HPDF_Page_SetHeight(page, (HPDF_REAL)(frame.bottom * 18. / 635.));
	nRead += sizeof(RECTL) * 2;
	fseek(f, 32, SEEK_CUR);
	SIZEL dev;
	fread(&dev, sizeof(SIZEL), 1, f); // frame 20-21
	PRINT_DBG("  mm %ix%i\r\n", dev.cx, dev.cy);
	xScale = (frame.right * 18.f) / (635.f * dev.cx);
	yScale = (frame.bottom * 18.f) / (635.f * dev.cy);
	scale = xScale > yScale ? xScale : yScale;
	nRead += 32+sizeof(SIZEL);
	currHeight = HPDF_Page_GetHeight(page);
	return nRead;
}

size_t Emf2Pdf::MoveToEx()
{
	POINTL p;
	fread(&p, sizeof(POINTL), 1, f); // pos
	currX = p.x * xScale;
	currY = currHeight - p.y * yScale;
	pathStartX = currX;
	pathStartY = currY;
	PRINT_DBG("  move to %i,%i\r\n", p.x, p.y);
	HPDF_Page_MoveTo(page, currX, currY);
	return sizeof(POINTL);
}

size_t Emf2Pdf::LineTo()
{
	POINTL p;
	fread(&p, sizeof(POINTL), 1, f); // pos
	currX = p.x * xScale;
	currY = currHeight - p.y * yScale;
	PRINT_DBG("  line to %i,%i\r\n", p.x, p.y);
	HPDF_Page_LineTo(page, currX, currY);
	if (!inPath) HPDF_Page_Stroke(page);
	return sizeof(POINTL);
}

size_t Emf2Pdf::PolyBezier(unsigned long code)
{
	size_t ret = sizeof(RECTL) + 4;
	RECTL r;
	fread(&r, sizeof(RECTL), 1, f); // pos
	unsigned long i,nPoint,j;
	fread(&nPoint, 4, 1, f); // pos
	PRINT_DBG("  bezier %i points\r\n", nPoint);
	for (i = 0; i < nPoint; i+=3)
	{
		HPDF_REAL x[3],y[3];
		if (code == EMR_POLYBEZIERTO16)
		{
			POINTS pt[3];
			fread(pt, sizeof(POINTS), 3, f); 
			ret += sizeof(POINTS) * 3;
			for (j = 0; j < 3; j++)
			{
				x[j] = pt[j].x * xScale;
				y[j] = currHeight - pt[j].y * yScale;
			}
			PRINT_DBG("  %i,%i %i,%i %i,%i\r\n", pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y );
		}
		else
		{
			POINTL pt[3];
			fread(pt, sizeof(POINTL), 3, f);
			ret += sizeof(POINTL) * 3;
			for (j = 0; j < 3; j++)
			{
				x[j] = pt[j].x * xScale;
				y[j] = currHeight - pt[j].y * yScale;
			}
			PRINT_DBG("  %i,%i %i,%i %i,%i\r\n", pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y);
		}
		HPDF_Page_CurveTo(page, x[0], y[0], x[1], y[1], x[2], y[2]);
		currX = x[2];
		currY = y[2];
	}
	return ret;
}

size_t Emf2Pdf::BeginPath()
{
	inPath = true;
	return 0;
}

size_t Emf2Pdf::EndPath()
{
	inPath = false;
	//HPDF_Page_EndPath(page);
	return 0;
}

size_t Emf2Pdf::FillPath()
{
	if(polyEO)
		HPDF_Page_Eofill(page);
	else
		HPDF_Page_Fill(page);
	return 0;
}

size_t Emf2Pdf::CloseFigure()
{
	if (currX != pathStartX || currY != pathStartY)
	{
#if defined(_CONSOLE_DEBUG)
		POINTL p;
		p.x = (LONG)(pathStartX / xScale);
		p.y = (LONG)(currHeight - (pathStartY / yScale));
		PRINT_DBG("  line to %i,%i\r\n", p.x, p.y);
#endif
		currX = pathStartX;
		currY = pathStartY;
		HPDF_Page_LineTo(page, currX, currY);
	}
	return 0;
}

size_t Emf2Pdf::SelectClipPath()
{
	// only copy supported
	//HPDF_Page_Clip(page);
	HPDF_Page_EndPath(page);
	return 0;
}

size_t Emf2Pdf::SelectObject()
{
	unsigned long obj;
	fread(&obj, 4, 1, f);
	if(obj>=0x80000000) {
		PRINT_DBG(" Obj 0x%8X\r\n", obj);
		switch (obj & 0xFF)
		{
		case WHITE_BRUSH:
			currentBrush.solid = true;
			currentBrush.r = currentBrush.g = currentBrush.b = 1.f;
			HPDF_Page_SetRGBFill(page, currentBrush.r, currentBrush.g, currentBrush.b);
			break;
		case LTGRAY_BRUSH:
			currentBrush.solid = true;
			currentBrush.r = currentBrush.g = currentBrush.b = 0.75f;
			HPDF_Page_SetRGBFill(page, currentBrush.r, currentBrush.g, currentBrush.b);
			break;
		case GRAY_BRUSH:
			currentBrush.solid = true;
			currentBrush.r = currentBrush.g = currentBrush.b = 0.5f;
			HPDF_Page_SetRGBFill(page, currentBrush.r, currentBrush.g, currentBrush.b);
			break;
		case DKGRAY_BRUSH:
			currentBrush.solid = true;
			currentBrush.r = currentBrush.g = currentBrush.b = 0.25f;
			HPDF_Page_SetRGBFill(page, currentBrush.r, currentBrush.g, currentBrush.b);
			break;
		case BLACK_BRUSH:
			currentBrush.solid = true;
			currentBrush.r = currentBrush.g = currentBrush.b = 0.f;
			HPDF_Page_SetRGBFill(page, currentBrush.r, currentBrush.g, currentBrush.b);
			break;
		case NULL_BRUSH:
			currentBrush.solid = false;
			break;
		case WHITE_PEN:
			currentPen.width = 1*scale;
			currentPen.r = currentPen.g = currentPen.b = 1.f;
			HPDF_Page_SetLineWidth(page, currentPen.width*scale);
			HPDF_Page_SetRGBStroke(page, currentPen.r, currentPen.g, currentPen.b);
			break;
		case BLACK_PEN:
			currentPen.width = 1 * scale;
			currentPen.r = currentPen.g = currentPen.b = 0.f;
			HPDF_Page_SetLineWidth(page, currentPen.width*scale);
			HPDF_Page_SetRGBStroke(page, currentPen.r, currentPen.g, currentPen.b);
			break;
		case NULL_PEN:
			currentPen.width = 0;
			currentPen.r = currentPen.g = currentPen.b = 0.f;
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
		PRINT_DBG(" Obj %i\r\n", obj);
		if (obj < nCreated)
		{
			CreatedItem& itm = created[obj];
			switch (itm.type)
			{
			case OBJ_PEN:
				currentPen.width = itm.pen.width;
				currentPen.r = itm.pen.r;
				currentPen.g = itm.pen.g;
				currentPen.b = itm.pen.b;
				HPDF_Page_SetLineWidth(page, currentPen.width*scale);
				HPDF_Page_SetRGBStroke(page, currentPen.r, currentPen.g, currentPen.b);
				break;
			case OBJ_BRUSH:
				currentBrush.solid = itm.brush.solid;
				currentBrush.r = itm.brush.r;
				currentBrush.g = itm.brush.g;
				currentBrush.b = itm.brush.b;
				HPDF_Page_SetRGBFill(page, currentBrush.r, currentBrush.g, currentBrush.b);
				break;
			}
		}
	}
	return 4;
}

size_t Emf2Pdf::SetTextColor()
{
	unsigned char r, g, b, x;
	fread(&r, 1, 1, f);
	fread(&g, 1, 1, f);
	fread(&b, 1, 1, f);
	fread(&x, 1, 1, f);
	rText = (float)r / 255.f;
	gText = (float)g / 255.f;
	bText = (float)b / 255.f;
	PRINT_DBG("  color %i %i %i", r, g, b);
	return 4;
}

void Emf2Pdf::SetCreatedIdx(unsigned long idx)
{
	if (nCreated == 0)
	{
		nCreated = idx + 1;
		created = (CreatedItem*)(malloc(sizeof(CreatedItem)*(idx + 1)));
	}
	else if (nCreated <= idx)
	{
		nCreated = idx + 1;
		created = (CreatedItem*)(realloc(created, sizeof(CreatedItem)*(idx + 1)));
	}
}

size_t Emf2Pdf::CreatePen()
{
	unsigned long  idx;
	fread(&idx, 4, 1, f);
	SetCreatedIdx(idx);
	created[idx].type = OBJ_PEN;
	unsigned long style,width;
	fread(&style, 4, 1, f); // temp: ignore
	fread(&width, 4, 1, f); // width
	created[idx].pen.width = scale * width;
	fread(&style, 4, 1, f); // to ignore
	unsigned char r, g, b, x;
	fread(&r, 1, 1, f);
	fread(&g, 1, 1, f);
	fread(&b, 1, 1, f);
	fread(&x, 1, 1, f);
	created[idx].pen.r = (float)r / 255.f;
	created[idx].pen.g = (float)g / 255.f;
	created[idx].pen.b = (float)b / 255.f;
	PRINT_DBG("  width %i rgb %i %i %i\r\n", width,r,g,b);
	return 20;
}

size_t Emf2Pdf::CreateBrush()
{
	unsigned long  idx;
	fread(&idx, 4, 1, f);
	SetCreatedIdx(idx);
	created[idx].type = OBJ_BRUSH;
	unsigned long style;
	fread(&style, 4, 1, f); // temp: ignore
	unsigned char r, g, b, x;
	fread(&r, 1, 1, f);
	fread(&g, 1, 1, f);
	fread(&b, 1, 1, f);
	fread(&x, 1, 1, f);
	created[idx].brush.r = (float)r / 255.f;
	created[idx].brush.g = (float)g / 255.f;
	created[idx].brush.b = (float)b / 255.f;
	PRINT_DBG("  rgb %i %i %i\r\n", r, g, b);
	return 12;
}

size_t Emf2Pdf::SetPolyFillMode()
{
	unsigned long nMode;
	fread(&nMode, 4, 1, f);
	polyEO = nMode == 1;
	PRINT_DBG("  %s\r\n", polyEO ? "EvenOdd" : "winding");
	return 4;
}


void Emf2Pdf::ParseFile()
{
	while (!feof(f))
	{
		unsigned long code, size;
		size_t r = fread(&code, sizeof(unsigned long), 1, f);
		if (r < 1) break;
		r = fread(&size, sizeof(unsigned long), 1, f);
		if (r < 1) break;
		size_t nRead = 8;
		PRINT_DBG("Record %i(%s) length %i (gMode 0x%04X)\r\n", code, emfNames[code - 1], size, page? HPDF_Page_GetGMode(page):0);
		switch (code)
		{
		case EMR_HEADER:				nRead += Header(); break;
		case EMR_SETTEXTCOLOR:			nRead += SetTextColor(); break;
		case EMR_MOVETOEX:				nRead += MoveToEx(); break;
		case EMR_SELECTOBJECT:			nRead += SelectObject(); break;
		case EMR_CREATEPEN:				nRead += CreatePen(); break;
		case EMR_CREATEBRUSHINDIRECT:	nRead += CreateBrush(); break;
		case EMR_LINETO:				nRead += LineTo(); break;
		case EMR_POLYBEZIERTO:
		case EMR_POLYBEZIERTO16:		nRead += PolyBezier(code); break;
		case EMR_BEGINPATH:				nRead += BeginPath(); break;
		case EMR_CLOSEFIGURE:			nRead += CloseFigure(); break;
		case EMR_ENDPATH:				nRead += EndPath(); break;
		case EMR_FILLPATH:				nRead += FillPath(); break;
		case EMR_SELECTCLIPPATH:		nRead += SelectClipPath(); break;
		case EMR_SETPOLYFILLMODE:		nRead += SetPolyFillMode(); break;
		}
		fseek(f, (long)(size - nRead), SEEK_CUR);
		HPDF_STATUS err = HPDF_GetError(pdf);
		if (err != HPDF_OK)
		{
			PRINT_DBG("HaruPDF Error 0x%4X", err);
			return;
		}
	}
}

bool Emf2Pdf::AddEMF(const char* cFileName)
{
	InitInstalledFont();
	Reset();
#ifdef WIN32
	errno_t err = fopen_s(&f, cFileName, "rb");
	if (err > 0)
	{
		PRINT_DBG("Error file %s - %i", cFileName, err);
		return false;
	}
#else
	f = fopen(cFileName, "rb");
#endif
	HPDF_Doc pdf = HPDF_New(0, 0);
	if (!f)
	{
		PRINT_DBG("File not found %s", cFileName);
		return false;
	}
	ParseFile();
	return true;
}

Emf2Pdf::SystemFont* Emf2Pdf::installedFont = 0;
void Emf2Pdf::InitInstalledFont()
{
	if (installedFont != 0) return;
	HKEY hFonts;
	LSTATUS result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts", 0, KEY_READ, &hFonts);
	if (result != ERROR_SUCCESS) return;
	DWORD maxValueNameSize, maxValueDataSize, nSubKeys;

	result = RegQueryInfoKey(hFonts, 0, 0, 0, &nSubKeys, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);

	if (result != ERROR_SUCCESS) return;
	installedFont = (Emf2Pdf::SystemFont*)malloc(sizeof(Emf2Pdf::SystemFont)*nSubKeys);
	LPSTR valueName = new CHAR[maxValueNameSize];

	LPBYTE valueData = new BYTE[maxValueDataSize];
	DWORD idxFont = 0;
	for (DWORD i = 0; i < nSubKeys; i++)
	{
		DWORD valueNameSize = maxValueNameSize, valueDataSize = maxValueDataSize;
		DWORD valueType;
		result = RegEnumValue(hFonts, i, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);
		if (result != ERROR_SUCCESS || valueType != REG_SZ) {

			continue;

		}
		installedFont[idxFont].name = new CHAR[valueNameSize];
		installedFont[idxFont].name = new CHAR[valueNameSize];
	}
}


//----------------------------------------------------TEST CODE--------------------------------------------------------
int main(int argc, const char* argv[])
{
	const char *fileToOpen = "illusion.emf";
	if (argc > 1) fileToOpen = argv[1];
	HPDF_Doc pdf = HPDF_New(0, 0);
	Emf2Pdf conv(pdf);
	conv.AddEMF(fileToOpen);
	if (HPDF_GetError(pdf) == HPDF_OK)
	{
		size_t l = strlen(fileToOpen);
		char *fileToSave = (char*)malloc(l + 2);
		strcpy_s(fileToSave, l + 2, fileToOpen);
		char *extension = strrchr(fileToSave, (int)'.');
		strcpy_s(extension, 5, ".pdf");
		HPDF_SaveToFile(pdf, fileToSave);
		PRINT_DBG("File salvato in %s\r\n", fileToSave);
	}
}
