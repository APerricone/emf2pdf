#include "Emf2Pdf.h"

//#define _CONSOLE_DEBUG
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
	"EMR_SETLINKEDUFIS", /*119*/
	"EMR_RESERVED_120", /*120*/
	"EMR_COLORMATCHTOTARGETW", /*121*/
	"EMR_CREATECOLORSPACEW", /*122*/
#endif
	"END"
};
#else
#define PRINT_DBG(...)
#endif

Emf2Pdf::Emf2Pdf(HPDF_Doc pdf)
{
	this->pdf = pdf;
	HPDF_SetCurrentEncoder(pdf, "WinAnsiEncoding");
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
	nCreated = 0;
	currX = currY = 0;
	currentFont.font = HPDF_GetFont(pdf, "Helvetica", 0);
	currentFont.height = 14;
	currentFont.width = 1;
	currentFont.fakeBold = currentFont.fakeItalic = false;
	currentFont.underline = currentFont.strike = false;
	currentPen.r = currentPen.g = currentPen.b = 0.f;
	currentPen.width = 1;
	currentPen.nDash = 0;
	currentPen.join = HPDF_ROUND_JOIN;
	currentPen.end = HPDF_ROUND_END;
	currentBrush.solid = true;
	currentBrush.r = currentBrush.g = currentBrush.b = 1.f;
	textAlign = 0;
	rText = gText = bText = 0.f;
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
	PRINT_DBG("  dev %ix%i\r\n", dev.cx, dev.cy);
	xScale = (frame.right * 18.f) / (635.f * dev.cx);
	yScale = (frame.bottom * 18.f) / (635.f * dev.cy);
	scale = xScale > yScale ? xScale : yScale;
	nRead += 32 + sizeof(SIZEL);
	currHeight = HPDF_Page_GetHeight(page);


	HPDF_Page_SetLineWidth(page, 1);
	HPDF_Page_SetRGBStroke(page, 0, 0, 0);
	HPDF_Page_SetDash(page, 0, 0, 0);
	HPDF_Page_SetLineCap(page, HPDF_ROUND_END);
	HPDF_Page_SetLineJoin(page, HPDF_ROUND_JOIN);
	HPDF_Page_SetRGBFill(page, 1, 1, 1);
	HPDF_Page_SetFontAndSize(page, HPDF_GetFont(pdf, "Helvetica", 0), 12);
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
	if (inPath)
		HPDF_Page_MoveTo(page, currX, currY);
	return sizeof(POINTL);
}

size_t Emf2Pdf::LineTo()
{
	POINTL p;
	fread(&p, sizeof(POINTL), 1, f); // pos
	PRINT_DBG("  line to %i,%i\r\n", p.x, p.y);
	if (!inPath) HPDF_Page_MoveTo(page, currX, currY);
	currX = p.x * xScale;
	currY = currHeight - p.y * yScale;
	HPDF_Page_LineTo(page, currX, currY);
	if (!inPath) HPDF_Page_Stroke(page);
	return sizeof(POINTL);
}

size_t Emf2Pdf::PolyBezier(unsigned long code)
{
	size_t ret = sizeof(RECTL) + 4;
	RECTL r;
	fread(&r, sizeof(RECTL), 1, f); // pos
	unsigned long i, nPoint, j;
	fread(&nPoint, 4, 1, f); // pos
	PRINT_DBG("  bezier %i points\r\n", nPoint);
	for (i = 0; i < nPoint; i += 3)
	{
		HPDF_REAL x[3], y[3];
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
			PRINT_DBG("  %i,%i %i,%i %i,%i\r\n", pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x, pt[2].y);
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
	if (polyEO)
		HPDF_Page_Eofill(page);
	else
		HPDF_Page_Fill(page);
	return 0;
}

size_t Emf2Pdf::StrokePath()
{
	HPDF_Page_Stroke(page);
	return 0;
}

size_t Emf2Pdf::StrokeAndFillPath()
{
	if (polyEO)
		HPDF_Page_EofillStroke(page);
	else
		HPDF_Page_FillStroke(page);
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
	if (inPath || HPDF_Page_GetGMode(page) == 2)
		HPDF_Page_EndPath(page);
	return 0;
}

size_t Emf2Pdf::SelectObject()
{
	unsigned long obj;
	fread(&obj, 4, 1, f);
	if (obj >= 0x80000000) {
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
			currentPen.width = 1 * scale;
			currentPen.r = currentPen.g = currentPen.b = 1.f;
			currentPen.nDash = 0;
			currentPen.join = HPDF_ROUND_JOIN;
			currentPen.end = HPDF_ROUND_END;
			HPDF_Page_SetLineWidth(page, currentPen.width*scale);
			HPDF_Page_SetRGBStroke(page, currentPen.r, currentPen.g, currentPen.b);
			HPDF_Page_SetDash(page, 0, 0, 0);
			HPDF_Page_SetLineCap(page, (HPDF_LineCap)currentPen.end);
			HPDF_Page_SetLineJoin(page, (HPDF_LineJoin)currentPen.join);
			break;
		case BLACK_PEN:
			currentPen.width = 1 * scale;
			currentPen.r = currentPen.g = currentPen.b = 0.f;
			currentPen.nDash = 0;
			currentPen.join = HPDF_ROUND_JOIN;
			currentPen.end = HPDF_ROUND_END;
			HPDF_Page_SetLineWidth(page, currentPen.width*scale);
			HPDF_Page_SetRGBStroke(page, currentPen.r, currentPen.g, currentPen.b);
			HPDF_Page_SetDash(page, 0, 0, 0);
			HPDF_Page_SetLineCap(page, (HPDF_LineCap)currentPen.end);
			HPDF_Page_SetLineJoin(page, (HPDF_LineJoin)currentPen.join);
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
	}
	else {
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
				currentPen.nDash = itm.pen.nDash;
				if (currentPen.nDash > 0)
					memcpy(currentPen.dash, itm.pen.dash, 2 * itm.pen.nDash);
				currentPen.end = itm.pen.end;
				currentPen.join = itm.pen.join;
				HPDF_Page_SetLineWidth(page, currentPen.width);
				HPDF_Page_SetRGBStroke(page, currentPen.r, currentPen.g, currentPen.b);
				HPDF_Page_SetDash(page, (const HPDF_UINT16*)currentPen.dash, currentPen.nDash, 0);
				HPDF_Page_SetLineCap(page, (HPDF_LineCap)currentPen.end);
				HPDF_Page_SetLineJoin(page, (HPDF_LineJoin)currentPen.join);
				break;
			case OBJ_BRUSH:
				currentBrush.solid = itm.brush.solid;
				currentBrush.r = itm.brush.r;
				currentBrush.g = itm.brush.g;
				currentBrush.b = itm.brush.b;
				HPDF_Page_SetRGBFill(page, currentBrush.r, currentBrush.g, currentBrush.b);
				break;
			case OBJ_FONT:
				currentFont.font = itm.font.font;
				currentFont.height = itm.font.height;
				currentFont.width = itm.font.width;
				currentFont.fakeBold = itm.font.fakeBold;
				currentFont.fakeItalic = itm.font.fakeItalic;
				currentFont.underline = itm.font.underline;
				currentFont.strike = itm.font.strike;
				HPDF_Page_SetFontAndSize(page, currentFont.font, currentFont.height);
				SetEncoding(itm.font.encoding);
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
	PRINT_DBG("  color %i %i %i\r\n", r, g, b);
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
	unsigned long style, width, h;
	fread(&style, 4, 1, f); // temp: ignore
	fread(&width, 4, 1, f); // width
	created[idx].pen.width = scale * width;
	fread(&h, 4, 1, f); // to ignore
	unsigned char r, g, b, x;
	fread(&r, 1, 1, f);
	fread(&g, 1, 1, f);
	fread(&b, 1, 1, f);
	fread(&x, 1, 1, f);
	created[idx].pen.r = (float)r / 255.f;
	created[idx].pen.g = (float)g / 255.f;
	created[idx].pen.b = (float)b / 255.f;
	PRINT_DBG("  width %i rgb %i %i %i\r\n", width, r, g, b);
	created[idx].pen.nDash = 0;
	switch (style&PS_STYLE_MASK)
	{
	case PS_SOLID:
		created[idx].pen.nDash = 0;
		break;
	case PS_DASH:
		created[idx].pen.dash[0] = 5;
		created[idx].pen.nDash = 1;
		break;
	case PS_DOT:
		created[idx].pen.dash[0] = 2;
		created[idx].pen.nDash = 1;
		break;
	case PS_DASHDOT:
		created[idx].pen.dash[0] = 5;
		created[idx].pen.dash[1] = 3;
		created[idx].pen.dash[2] = 1;
		created[idx].pen.dash[3] = 3;
		created[idx].pen.nDash = 4;
		break;
	case PS_DASHDOTDOT:
		created[idx].pen.dash[0] = 5;
		created[idx].pen.dash[1] = 3;
		created[idx].pen.dash[2] = 1;
		created[idx].pen.dash[3] = 3;
		created[idx].pen.dash[4] = 1;
		created[idx].pen.dash[5] = 3;
		created[idx].pen.nDash = 6;
		break;
	case PS_NULL:
		created[idx].pen.width = 0;
		break;
	}
	switch (style & PS_ENDCAP_MASK)
	{
	case PS_ENDCAP_ROUND:
		created[idx].pen.end = HPDF_ROUND_END;
		break;
	case PS_ENDCAP_SQUARE:
		created[idx].pen.end = HPDF_PROJECTING_SCUARE_END;
		break;
	case PS_ENDCAP_FLAT:
		created[idx].pen.end = HPDF_BUTT_END;
		break;
	}
	switch (style & PS_JOIN_MASK)
	{
	case PS_JOIN_ROUND:
		created[idx].pen.join = HPDF_ROUND_JOIN;
		break;
	case PS_JOIN_BEVEL:
		created[idx].pen.join = HPDF_BEVEL_JOIN;
		break;
	case PS_JOIN_MITER:
		created[idx].pen.join = HPDF_MITER_JOIN;
		break;
	}
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
	created[idx].brush.solid = true;
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

int Emf2Pdf::FindFont(wchar_t* faceName, bool bold, bool italic)
{
	for (int i = 0; i < nInstalledFont; i++)
	{
		if (wcswcs(installedFont[i].name, faceName) == 0) continue;
		bool isbold = wcswcs(installedFont[i].name, L" bold ");
		if (isbold != bold) continue;
		bool isitalic = wcswcs(installedFont[i].name, L" italic ");
		if (isitalic != italic) continue;
		return i;
	}
	return -1;
}

const char *Emf2Pdf::GetEncoding(unsigned char idx)
{
	switch (idx)
	{
	case ANSI_CHARSET:			return ("WinAnsiEncoding"); break;
	case DEFAULT_CHARSET:		return ("StandardEncoding"); break;
	case SYMBOL_CHARSET:		break;
	case MAC_CHARSET:			return ("MacRomanEncoding"); break;
	case SHIFTJIS_CHARSET:		return ("90ms-RKSJ-H"); break;
	case HANGUL_CHARSET:		return ("KSCms-UHC-H"); break;
	case JOHAB_CHARSET:			break;
	case GB2312_CHARSET:		break;
	case CHINESEBIG5_CHARSET:	break;
	case GREEK_CHARSET:			return ("CP1253"); break;
	case TURKISH_CHARSET:		return ("CP1254"); break;
	case VIETNAMESE_CHARSET:	return ("CP1258"); break;
	case HEBREW_CHARSET:		return ("CP1255"); break;
	case ARABIC_CHARSET:		return ("CP1256"); break;
	case BALTIC_CHARSET:		return ("CP1257"); break;
	case RUSSIAN_CHARSET:		return ("KOI8-R"); break;
	case THAI_CHARSET:	 		return ("ISO8859-11"); break;
	case EASTEUROPE_CHARSET:	break;
	case OEM_CHARSET:			break;
	}
	return 0;
}

void Emf2Pdf::SetEncoding(unsigned char idx)
{
	const char *name = GetEncoding(idx);
	if (name)
		HPDF_SetCurrentEncoder(pdf, name);
}

size_t Emf2Pdf::CreatePDFFont()
{
	InitInstalledFont();
	size_t ret = 4;
	unsigned long  idx;
	fread(&idx, 4, 1, f);
	SetCreatedIdx(idx);
	long height, width, weight;
	fread(&height, 4, 1, f); ret += 4;
	fread(&width, 4, 1, f); ret += 4;
	fseek(f, 8, SEEK_CUR); ret += 8;
	fread(&weight, 4, 1, f); ret += 4;
	char cItalic, encoding, underline, strikeOut;
	fread(&cItalic, 1, 1, f); ret += 1;
	fread(&underline, 1, 1, f); ret += 1;
	fread(&strikeOut, 1, 1, f); ret += 1;
	fread(&encoding, 1, 1, f); ret += 1;
	fseek(f, 4, SEEK_CUR); ret += 4;
	wchar_t faceName[32];
	fread(faceName, 2, 32, f); ret += 64;
	wchar_t *tl = faceName;
	while (*tl) *tl++ = towlower(*tl);
	bool bold = weight > 550, italic = cItalic > 0;
	bool fakeBold = false, fakeItalic = false;
	PRINT_DBG("  %S %s%s%ix%i\r\n", faceName, bold ? "bold " : "", italic ? "italic " : "", height, width);
	int i = FindFont(faceName, bold, italic);
	if (i < 0)
	{
		if (bold && italic)
		{
			i = FindFont(faceName, false, italic);
			if (i >= 0) {
				fakeBold = true;
			}
			else {
				i = FindFont(faceName, bold, false);
				if (i >= 0) {
					fakeItalic = true;
				}
				else {
					i = FindFont(faceName, false, false);
					fakeItalic = true;
					fakeBold = true;
				}
			}
		}
		else if (bold || italic)
		{
			i = FindFont(faceName, false, false);
			fakeItalic = italic;
			fakeBold = bold;
		}
	}
	if (i >= 0)
	{
		created[idx].type = OBJ_FONT;
		const char* loaded = HPDF_LoadTTFontFromFile(pdf, installedFont[i].path, false);
		created[idx].font.font = HPDF_GetFont(pdf, loaded, GetEncoding(encoding));
		HPDF_INT a = HPDF_Font_GetAscent(created[idx].font.font), d = HPDF_Font_GetDescent(created[idx].font.font);
		HPDF_Box bx = HPDF_Font_GetBBox(created[idx].font.font);
		if (height < 0)
		{
			created[idx].font.height = -height * yScale;
		}
		else
		{
			float sc = (float)(a - d) / (float)(bx.top - bx.bottom);
			created[idx].font.height = height * sc * yScale;
		}
		if (created[idx].font.height > 200) created[idx].font.height = 100;
		HPDF_Page_SetFontAndSize(page, created[idx].font.font, created[idx].font.height);
		created[idx].font.width = 1;
		if (width != 0)
		{
			float currWidth; // = (bx.right - bx.left) *created[idx].font.height / (bx.top - bx.bottom);
			HPDF_Font_MeasureText(created[idx].font.font, (const HPDF_BYTE*)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", 62,
				1e10, created[idx].font.height, 0, 0, HPDF_FALSE, &currWidth);
			currWidth /= 62;
			created[idx].font.width = width * xScale / currWidth;
		}
		created[idx].font.fakeBold = fakeBold;
		created[idx].font.fakeItalic = fakeItalic;
		created[idx].font.underline = underline == 1;
		created[idx].font.strike = strikeOut == 1;
		created[idx].font.encoding = encoding;
	}
	else
	{
		PRINT_DBG("  NON TROVATO");
	}
	return ret;
}

size_t Emf2Pdf::SetTextAlign()
{
	unsigned long mode;
	fread(&mode, 4, 1, f);
	textAlign = (DWORD)(mode & 0xFFFF);
	return 4;
}

size_t Emf2Pdf::PDFTextOut(unsigned long code)
{
	size_t ret = 20;
	fseek(f, 16, SEEK_CUR); //bound and graphics mode
	unsigned long gm;
	fread(&gm, 4, 1, f);
	float font_xScale, font_yScale;
	fread(&font_xScale, 4, 1, f); ret += 4;
	fread(&font_yScale, 4, 1, f); ret += 4;
	POINTL pos;
	fread(&pos, 8, 1, f); ret += 8;
	float nItalic = currentFont.fakeItalic ? 0.333f : 0;
	unsigned long nChar, strOff, dxOff;
	RECTL rect;
	fread(&nChar, 4, 1, f); ret += 4;
	fread(&strOff, 4, 1, f); ret += 4; strOff -= 8;
	unsigned long opts;
	fread(&opts, 4, 1, f); ret += 4;//opts
	fread(&rect, 16, 1, f); ret += 16;
	fread(&dxOff, 4, 1, f); ret += 4; dxOff -= 8;
	if (strOff > ret) fseek(f, (long)(strOff - ret), SEEK_CUR); ret = strOff;
	char *str = (char*)malloc(sizeof(char)*(nChar + 1));
	str[nChar] = 0;
	size_t ll;
	if (code == EMR_EXTTEXTOUTW)
	{
		wchar_t *strw = (wchar_t*)malloc(sizeof(wchar_t)*(nChar + 1));
		strw[nChar] = 0;
		fread(strw, sizeof(wchar_t), nChar, f);  ret += sizeof(wchar_t)*nChar;
		wcstombs_s(&ll, str, nChar + 1, strw, nChar + 1);
		free(strw);
		ll -= 1;
	}
	else
	{
		fread(str, 1, nChar, f); ret += nChar;
		ll = strlen(str);
	}
	if (dxOff > ret) fseek(f, dxOff - ret, SEEK_CUR); ret = dxOff;
	PRINT_DBG("  %i,%i -> %s\r\n", pos.x, pos.y, str);
	if (ll <= 0) return ret;
	HPDF_Page_BeginText(page);
	HPDF_Page_SetRGBFill(page, rText, gText, bText);
	HPDF_Page_SetRGBStroke(page, rText, gText, bText);
	float size = HPDF_Page_GetCurrentFontSize(page);
	HPDF_Page_SetLineWidth(page, size / 20.f);
	if (currentFont.fakeBold)
		HPDF_Page_SetTextRenderingMode(page, HPDF_FILL_THEN_STROKE);
	HPDF_Page_SetTextMatrix(page, currentFont.width, 0, currentFont.width * nItalic, 1, 0, 0);

	unsigned long* dx = (unsigned long*)malloc(sizeof(unsigned long)*nChar);
	fread(dx, sizeof(unsigned long), nChar, f);  ret += sizeof(unsigned long)*nChar;
	float y = currHeight - pos.y * yScale;
	if ((textAlign & TA_BASELINE) != TA_BASELINE)
	{// baseline is the default for haru
		if (textAlign & TA_BOTTOM)
		{
			y -= HPDF_Font_GetDescent(currentFont.font) * size / 1024;
		}
		else
		{

			y -= HPDF_Font_GetAscent(currentFont.font) * size / 1024;
		}
	}
	//float y0 = currHeight - rect.bottom*yScale;
	//float y1 = currHeight - rect.top*yScale;
	char out[2]; out[1] = 0;
	float startX, endX;
	float x = pos.x * xScale;
	float endW;
	if (textAlign & TA_RIGHT)
	{		
		if (opts & ETO_CLIPPED) x = rect.right * xScale;
		endX = x+ HPDF_Font_GetUnicodeWidth(currentFont.font, str[ll-1])  * size / 1000;
		endW = -1e20f;
		if (opts & ETO_CLIPPED) endW = rect.left * xScale;
		for (int i = ll - 1, j = nChar - 1; i >= 0; i--, j--)
		{
			out[0] = str[i];
			x -= dx[j] * xScale;
			HPDF_Page_TextOut(page, x, y, out);
			if (x < endW)
				break;
		}
		startX = x;
	}
	else if (textAlign & TA_CENTER)
	{
		//TODO
	}
	else
	{
		if (opts & ETO_CLIPPED) x = rect.left * xScale;
		startX = x;
		endW = 1e20f;
		if (opts & ETO_CLIPPED) endW = rect.right * xScale;
		unsigned int i;
		for (i = 0; i < nChar && i < ll; i++)
		{
			out[0] = str[i];
			HPDF_Page_TextOut(page, x, y, out);
			x += dx[i] * xScale;
			if (x > endW)
			{
				x-= dx[i] * xScale;
				i += 1;
				break;
			}
		}
		endX = x; // +HPDF_Font_GetUnicodeWidth(currentFont.font, str[i - 1])  * currentFont.height / 1000;
	}
	free(str);
	free(dx);
	HPDF_Page_EndText(page);
	HPDF_Page_SetTextRenderingMode(page, HPDF_FILL);
	if (currentFont.underline)
	{
		HPDF_Page_MoveTo(page, startX, y - size / 10);
		HPDF_Page_LineTo(page, endX, y - size / 10);
	}
	if (currentFont.strike)
	{
		HPDF_Page_MoveTo(page, startX, y + size / 2);
		HPDF_Page_LineTo(page, endX, y + size / 2);
	}
	if (currentFont.strike || currentFont.underline)
		HPDF_Page_Stroke(page);
	return ret;
}

size_t Emf2Pdf::StretchDiBits(unsigned long code)
{
	size_t ret = 0;
	POINTL dest, destSize;
	fseek(f, 16, SEEK_CUR);  ret += 16;
	unsigned int offHdr=0, dimHdr=0, offBits=0, dimBits=0, usage=0, oper=0;
	dest.x=dest.y=destSize.x=destSize.y=0;
	switch (code)
	{
	case EMR_BITBLT:
		fread(&dest, 4, 2, f); ret += 8;
		fread(&destSize, 4, 2, f); ret += 8;
		fread(&oper, 4, 1, f); ret += 4;
		fseek(f, 28, SEEK_CUR);  ret += 28;
		fread(&usage, 4, 1, f); ret += 4;
		fread(&offHdr, 4, 1, f); ret += 4; offHdr -= 8;
		fread(&dimHdr, 4, 1, f); ret += 4;
		fread(&offBits, 4, 1, f); ret += 4; offBits -= 8;
		fread(&dimBits, 4, 1, f); ret += 4;
		break;
	case EMR_STRETCHDIBITS:
		fread(&dest, 4, 2, f); ret += 8;
		fseek(f, 16, SEEK_CUR);  ret += 16;
		fread(&offHdr, 4, 1, f); ret += 4; offHdr -= 8;
		fread(&dimHdr, 4, 1, f); ret += 4;
		fread(&offBits, 4, 1, f); ret += 4; offBits -= 8;
		fread(&dimBits, 4, 1, f); ret += 4;
		fread(&usage, 4, 1, f); ret += 4;
		fread(&oper, 4, 1, f); ret += 4;
		fread(&destSize, 4, 2, f); ret += 8;
		break;
	}
	if (dimHdr == 0 || dimBits == 0)
	{
		float x, y, w, h;
		x = dest.x * xScale;
		y = currHeight - (dest.y + destSize.y) * yScale;
		w = destSize.x * xScale;
		h = destSize.y * yScale;
		HPDF_Page_Rectangle(page, x, y, w, h);
		HPDF_Page_Fill(page);
		return ret;
	}
	if (usage != 0) return ret; //only RGB
	//if (oper != SRCCOPY) 	return ret; //only copy
	if (offHdr + dimHdr > offBits)
		return ret;
	if (ret < offHdr) {
		fseek(f, offHdr - ret, SEEK_CUR);
		ret = offHdr;
	}
	BITMAPINFOHEADER bmi;
	bmi.biSize = 0;
	if (dimHdr >= sizeof(BITMAPINFOHEADER))
	{
		fread(&bmi, sizeof(BITMAPINFOHEADER), 1, f); ret += sizeof(BITMAPINFOHEADER);
	}
	else
		return ret;
	if (bmi.biSize < sizeof(BITMAPINFOHEADER))
		return ret;
	//*/
	RGBQUAD *palette = 0;
	if (bmi.biClrUsed > 0)
	{
		if (bmi.biSize > sizeof(BITMAPINFOHEADER))
		{
			fseek(f, bmi.biSize - sizeof(BITMAPINFOHEADER), SEEK_CUR);
			ret += bmi.biSize - sizeof(BITMAPINFOHEADER);
		}
		palette = (RGBQUAD*)(malloc(sizeof(RGBQUAD)*bmi.biClrUsed));
		fread(palette, sizeof(RGBQUAD), bmi.biClrUsed, f);
		ret += sizeof(RGBQUAD)*bmi.biClrUsed;
	}
	if (ret < offBits) {
		fseek(f, offBits - ret, SEEK_CUR);
		ret = offBits;
	}
	unsigned char *bits = (unsigned char*)malloc(dimBits);
	fread(bits, 1, dimBits, f); ret += dimBits;
	HPDF_Image img;
	if (bmi.biCompression == BI_PNG)
	{
		img = HPDF_LoadPngImageFromMem(pdf, bits, dimBits);
	}
	else if (bmi.biCompression == BI_JPEG)
	{
		img = HPDF_LoadJpegImageFromMem(pdf, bits, dimBits);
	}
	else if (bmi.biCompression == BI_RGB)
	{
		HPDF_ColorSpace cs = (bmi.biBitCount < 16 ? HPDF_CS_DEVICE_GRAY : HPDF_CS_DEVICE_RGB);
		HPDF_UINT nBit=1;
		unsigned char* destPtr = bits, tmp, *src = bits, *newB;
		unsigned long i;
		switch (bmi.biBitCount)
		{
		case 1:
			cs = HPDF_CS_DEVICE_GRAY;
			nBit = 1;
			break;
		case 4:
			if (bmi.biClrUsed > 0)
			{
				newB = (unsigned char*)malloc(bmi.biWidth*bmi.biHeight * 3);
				destPtr = newB;
				for (i = 0; i < (unsigned)(bmi.biWidth*bmi.biHeight); i += 2, destPtr += 6, src += 1)
				{
					destPtr[0] = palette[(*src & 0x0F0) >> 4].rgbRed;
					destPtr[1] = palette[(*src & 0x0F0) >> 4].rgbGreen;
					destPtr[2] = palette[(*src & 0x0F0) >> 4].rgbBlue;
					destPtr[3] = palette[*src & 0x0F].rgbRed;
					destPtr[4] = palette[*src & 0x0F].rgbGreen;
					destPtr[5] = palette[*src & 0x0F].rgbBlue;
				}
				free(bits);
				bits = newB;
				cs = HPDF_CS_DEVICE_RGB;
				nBit = 8;
			}
			else
			{
				if (palette) free(palette);
				free(bits);
				return ret;
			}
			break;
		case 8:
			if (bmi.biClrUsed > 0)
			{
				newB = (unsigned char*)malloc(bmi.biWidth*bmi.biHeight * 3);
				destPtr = newB;
				for (i = 0; i < (unsigned)(bmi.biWidth*bmi.biHeight); i++, destPtr += 3, src += 1)
				{
					destPtr[0] = palette[*src].rgbRed;
					destPtr[1] = palette[*src].rgbGreen;
					destPtr[2] = palette[*src].rgbBlue;
				}
				free(bits);
				bits = newB;
				cs = HPDF_CS_DEVICE_RGB;
				nBit = 8;
			}
			else
			{
				cs = HPDF_CS_DEVICE_GRAY;
				nBit = 8;
			}
			break;
		case 16:
			if (palette) free(palette);
			free(bits);
			return ret;
			break;
		case 24:
			cs = HPDF_CS_DEVICE_RGB;
			nBit = 8;
			for (i = 0; i < dimBits; i += 3, destPtr += 3)
			{
				tmp = destPtr[0];
				destPtr[0] = destPtr[2];
				destPtr[2] = tmp;
			}
			break;
		case 32:
			cs = HPDF_CS_DEVICE_RGB;
			nBit = 8;
			for (i = 0; i < dimBits; i += 3, destPtr += 3, src += 4)
			{
				tmp = src[0];
				destPtr[0] = src[2];
				destPtr[1] = src[1];
				destPtr[2] = tmp;
			}
			break;
		}

		img = HPDF_LoadRawImageFromMem(pdf, bits, bmi.biWidth, bmi.biHeight, cs, nBit);
	}
	else {
		if (palette) free(palette);
		free(bits);
		return ret;
	}
	float x, y, w, h;
	x = dest.x * xScale;
	y = currHeight - dest.y * yScale;
	w = destSize.x * xScale;
	h = destSize.y * yScale;
	HPDF_Page_DrawImage(page, img, x, y, w, -h);

	if (palette) free(palette);
	free(bits);
	return ret;
}

size_t Emf2Pdf::Polygon(unsigned long code)
{
	size_t ret = 0;
	RECTL bound;
	fread(&bound, 4, 4, f); ret += 16;
	unsigned long nPoint;
	fread(&nPoint, 4, 1, f); ret += 4;
	PRINT_DBG("  %i points\r\n", nPoint);
	float startX=0, startY=0;
	for (unsigned long i = 0; i < nPoint; i++)
	{
		float x, y;
		if (code == EMR_POLYGON)
		{
			POINTL p;
			fread(&p, 4, 2, f); ret += 8;
			PRINT_DBG("  %i %i,%i\r\n", i, p.x, p.y);
			x = p.x * xScale;
			y = currHeight - p.y * yScale;
		}
		else
		{
			POINTS p;
			fread(&p, 2, 2, f); ret += 4;
			PRINT_DBG("  %i %i,%i\r\n", i, p.x, p.y);
			x = p.x * xScale;
			y = currHeight - p.y * yScale;
		}
		if (i == 0) {
			HPDF_Page_MoveTo(page, x, y);
			startX = x;
			startY = y;
		}
		else HPDF_Page_LineTo(page, x, y);
	}
	HPDF_Page_LineTo(page, startX, startY);
	if (currentPen.width > 0 && currentBrush.solid)
	{
		HPDF_Page_FillStroke(page);
	}
	else if (currentPen.width > 0)
	{
		HPDF_Page_Stroke(page);
	}
	else if (currentBrush.solid)
	{
		HPDF_Page_Fill(page);
	}
	return ret;
}

size_t Emf2Pdf::Ellipse()
{
	RECTL bound;
	fread(&bound, 4, 4, f);
	float x = (bound.right + bound.left) * xScale / 2;
	float y = currHeight - (bound.top + bound.bottom) * xScale / 2;
	float rx = (bound.right - bound.left) * xScale / 2;
	float ry = (bound.bottom - bound.top) * yScale / 2;
	HPDF_Page_Ellipse(page, x, y, rx, ry);

	if (currentPen.width > 0 && currentBrush.solid)
	{
		HPDF_Page_FillStroke(page);
	}
	else if (currentPen.width > 0)
	{
		HPDF_Page_Stroke(page);
	}
	else if (currentBrush.solid)
	{
		HPDF_Page_Fill(page);
	}

	return 16;
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
		PRINT_DBG("Record %i(%s) length %i (gMode 0x%04X)\r\n", code, emfNames[code - 1], size, page ? HPDF_Page_GetGMode(page) : 0);
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
		case EMR_STROKEPATH:			nRead += StrokePath(); break;
		case EMR_STROKEANDFILLPATH:		nRead += StrokeAndFillPath(); break;
		case EMR_SELECTCLIPPATH:		nRead += SelectClipPath(); break;
		case EMR_SETPOLYFILLMODE:		nRead += SetPolyFillMode(); break;
		case EMR_EXTCREATEFONTINDIRECTW:nRead += CreatePDFFont(); break;
		case EMR_EXTTEXTOUTW:
		case EMR_EXTTEXTOUTA:			nRead += PDFTextOut(code); break;
		case EMR_SETTEXTALIGN:			nRead += SetTextAlign(); break;
		case EMR_BITBLT:
		case EMR_STRETCHDIBITS:			nRead += StretchDiBits(code); break;
		case EMR_POLYGON:
		case EMR_POLYGON16:				nRead += Polygon(code); break;
		case EMR_ELLIPSE:				nRead += Ellipse(); break;
		case EMR_EOF: return;
		}
		fseek(f, (long)(size - nRead), SEEK_CUR);
		HPDF_STATUS err = HPDF_GetError(pdf);
		if (err != HPDF_OK)
		{
			PRINT_DBG("HaruPDF Error 0x%4X (gMode 0x%04X)", err, page ? HPDF_Page_GetGMode(page) : 0);
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
	if (!f)
	{
		PRINT_DBG("File not found %s", cFileName);
		return false;
	}
	ParseFile();
	return true;
}

int Emf2Pdf::nInstalledFont = 0;
Emf2Pdf::SystemFont* Emf2Pdf::installedFont = 0;
void Emf2Pdf::InitInstalledFont()
{
	if (installedFont != 0) return;
	HKEY hFonts;
	LSTATUS result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts", 0, KEY_READ, &hFonts);
	if (result != ERROR_SUCCESS) return;
	DWORD maxValueNameSize, maxValueDataSize, nValues;

	result = RegQueryInfoKey(hFonts, 0, 0, 0, 0, 0, 0, &nValues, &maxValueNameSize, &maxValueDataSize, 0, 0);

	if (result != ERROR_SUCCESS)
	{
		RegCloseKey(hFonts);
		return;
	}
	installedFont = (Emf2Pdf::SystemFont*)malloc(sizeof(Emf2Pdf::SystemFont)*nValues);
	LPWSTR valueName = new WCHAR[maxValueNameSize];
	LPWSTR valueData = new WCHAR[maxValueDataSize];
	LPSTR tmpValData = new CHAR[maxValueDataSize];
	DWORD idxFont = 0;
	char winDir[MAX_PATH];
	GetSystemWindowsDirectoryA(winDir, MAX_PATH);
	strcat_s<MAX_PATH>(winDir, "\\fonts\\");
	size_t windDirPath = strlen(winDir);
	for (DWORD i = 0; i < nValues; i++)
	{
		DWORD valueNameSize = maxValueNameSize, valueDataSize = maxValueDataSize;
		DWORD valueType;
		result = RegEnumValueW(hFonts, i, valueName, &valueNameSize, 0, &valueType, (LPBYTE)valueData, &valueDataSize);
		if (result != ERROR_SUCCESS || valueType != REG_SZ) {
			continue;
		}
		size_t lName = wcslen(valueName) + 1;
		size_t lData = wcslen(valueData) + 1;
		installedFont[idxFont].name = new WCHAR[lName];
		installedFont[idxFont].path = new CHAR[windDirPath + lData];
		wchar_t *tl = valueName;
		while (*tl) *tl++ = towlower(*tl);
		wcscpy_s(installedFont[idxFont].name, lName, (wchar_t*)valueName);
		strcpy_s(installedFont[idxFont].path, windDirPath + lData, winDir);
		size_t tmp;
		wcstombs_s(&tmp, tmpValData, maxValueDataSize, valueData, maxValueDataSize);
		strcat_s(installedFont[idxFont].path, windDirPath + lData, tmpValData);
		idxFont += 1;
	}
	delete[] valueName;
	delete[] valueData;
	delete[] tmpValData;
	RegCloseKey(hFonts);
	nInstalledFont = idxFont;
}

#ifdef __HARBOUR__

#include <hbapi.h>
#include <hbhpdf.h>

HB_FUNC(HPDF_ADDEMF) // pdf (Pointer), cEMFFIle (stringa)
{
	HPDF_Doc pdf = hb_HPDF_Doc_par(1);
	if (pdf == 0)
	{
		hb_ret();
		return;
	}
	Emf2Pdf conv(pdf);
	conv.AddEMF(hb_parc(2));
	hb_ret();
}

#endif
