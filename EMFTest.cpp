// EMFTest.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include "pch.h"

int main(int argc, const char* argv[])
{/*
	HPDF_Doc pdf = HPDF_New(0, 0);
	Emf2Pdf conv(pdf);
	conv.AddEMF("rep01.emf");
	if (HPDF_GetError(pdf) == HPDF_OK) conv.AddEMF("261465000.emf");
	//if (HPDF_GetError(pdf) == HPDF_OK) conv.AddEMF("rep02.emf");
	//if (HPDF_GetError(pdf) == HPDF_OK) conv.AddEMF("rep03.emf");
	//if (HPDF_GetError(pdf) == HPDF_OK) conv.AddEMF("rep04.emf");
	//if (HPDF_GetError(pdf) == HPDF_OK) conv.AddEMF("rep05.emf");
	//if (HPDF_GetError(pdf) == HPDF_OK) conv.AddEMF("rep06.emf");
	if (HPDF_GetError(pdf) == HPDF_OK) HPDF_SaveToFile(pdf, "rep.pdf");

	/*/
	const char *fileToOpen;
	fileToOpen = "mandala.emf"; 
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
		printf("File salvato in %s\r\n", fileToSave);
	}//*/
}
