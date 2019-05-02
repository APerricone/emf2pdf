#pragma once

#include <stdio.h>
#include <hpdf.h>
#include <windows.h>

class Emf2Pdf
{
public:

	Emf2Pdf(HPDF_Doc pdf);
	~Emf2Pdf();

	bool AddEMF(const char* cFileName);

private:
	struct SystemFont
	{
		wchar_t* name;
		char* path;
	};
	static int nInstalledFont;
	static SystemFont* installedFont;
	static void InitInstalledFont();
	static int FindFont(wchar_t* faceName, bool bold, bool italic);
	const char *GetEncoding(unsigned char idx);
	void SetEncoding(unsigned char idx);

	struct Font
	{
		HPDF_Font font;
		float height, width;
		bool fakeBold;
		bool fakeItalic;
		bool underline;
		bool strike;
		unsigned char encoding;
	};

	struct Pen
	{
		float width, r, g, b;
		WORD dash[8];
		UINT nDash;
		unsigned char join;
		unsigned char end;
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
	DWORD textAlign;
	float rText, gText, bText;
	float rTextBck, gTextBck, bTextBck;
	bool textBKOpaque;
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
	size_t StrokePath();
	size_t StrokeAndFillPath();
	size_t SelectClipPath();
	size_t SetPolyFillMode();
	size_t CreatePDFFont();
	size_t PDFTextOut(unsigned long code);
	size_t SetTextAlign();
	size_t StretchDiBits(unsigned long code);
	size_t Polygon(unsigned long code);
	size_t Ellipse();
	size_t SetBkColor();
	size_t SetBkMode ();

	void ParseFile();
};
