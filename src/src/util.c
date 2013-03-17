/*
	Project: ProcessString
	Functional area: Util macroses, inluding libs
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 05.03.2013
*/

#include "S:\h\util.h"

#ifdef WIN
HANDLE g_hSTDOut = NULL;
void setColor(WORD col)
{
	if (!g_hSTDOut)
	{
		g_hSTDOut = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	SetConsoleTextAttribute(g_hSTDOut, col|FOREGROUND_INTENSITY);
}
#endif
