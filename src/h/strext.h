/*
	Project: ProcessString
	Functional area: Extended C-string functions
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 22.02.2013
*/

#ifndef _STR_EXT_INCLUDED_
#define _STR_EXT_INCLUDED_

#include "S:\h\util.h"

/* function deletes one string template in input string
   return TRUE in case success 
   even if template sring was not found */
int delStrTeml(char* str, const char* templ);

/* create string < newFile *.<s_input_file_ext> >.<s_output_file_ext> */
void fillOutputFileName(char* newFile);

/* remove symbols less then MIN_COR_SYM from str */
extern void removeBadSymb(char *str);

/* func check string for bad symbols */
int noBadSymbols(const char* str);

/* returns TRUE if str contains symbol ch*/
int containsSymbol(const char* str, char ch);

/* tell is symbols available for file name symbol*/
int checkSymbol(char c);

#endif /*_STR_EXT_INCLUDED_*/
