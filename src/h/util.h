/*
	Project: laba1-14
	Functional area: Util macroses, inluding libs
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 22.02.2013
*/

#ifndef _UTIL_INCLUDED_
#define _UTIL_INCLUDED_

/* external libs */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "S:\h\config.h"

#ifdef WIN
   #include <windows.h>
#endif 

/* implements color debug console */
#ifdef WIN
HANDLE g_hSTDOut;
void setColor(WORD col);
#endif

/* debug printf implementation */
// =======================================
#if defined(DEBUG) && defined(WIN)
// =======================================
# define DEBUG_PRINT(x) setColor(FOREGROUND_BLUE | FOREGROUND_GREEN); \
printf("[%s]%s:%i ", \
__FILE__,__PRETTY_FUNCTION__ ,__LINE__ ); \
setColor(FOREGROUND_GREEN); \
printf x ; \
setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#define DEBUG_SYSTEM(x) system(x);
// =======================================
#else
// =======================================
#define DEBUG_PRINT(x) 
#define DEBUG_SYSTEM(x) 
// =======================================
#endif
// =======================================

#endif /*_UTIL_INCLUDED_*/