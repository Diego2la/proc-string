/*
	Project: laba1-14
	Functional area: Extended C-string functions
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 22.02.2013
*/

#include "S:\h\strext.h"

int delStrTeml(char* str, const char* templ)
{
	int res = FALSE;
	if (str && templ)
	{
		DEBUG_PRINT(("Starting delStrTeml\n"));	
		int strLen   = strlen(str)
		  , templLen = strlen(templ)
		  , i;
		  
		/* find first entry */
		char* entry = strstr(str, templ);
		
		if (entry != NULL)
		{	
			DEBUG_PRINT(("entry not null\n"));	
			/* shift str and filling free space with '\0' */
			for (i = entry - str; i < strLen; ++i)
			{
				str[i] = (i + templLen < strLen) ? str[i + templLen] : '\0';
			}
		}
		res = TRUE;
	}
	return res;
}

void fillOutputFileName(char* newFile)
{
	char *point = strrchr(newFile, '.');
	assert(point);
	newFile[point - newFile] = '\0';
	strcat(newFile, s_output_file_ext);
}

void removeBadSymb(char *str) 
{
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) 
	{
        *dst = *src;
        if (*dst >= MIN_COR_SYM) dst++;
    }
    *dst = '\0';
}

int noBadSymbols(const char* str)
{
	int i = 0;
	for (i = 0; i < strlen(str); ++i)
	{
		if ( checkSymbol(str[i]) == FALSE )
			return FALSE;
	}
	return TRUE;
}

int containsSymbol(const char* str, char ch)
{
	int i;
	for (i = 0; i < strlen(str); ++i)
	{
		if (str[i] == ch)
			return TRUE;
	}
	return FALSE;
}

int checkSymbol(char c)
{
	if ( c >= '0' && c <= '9' )
		return TRUE;
	if ( c >= 'A' && c <= 'Z' )
		return TRUE;
	if ( c >= 'a' && c <= 'z' )
		return TRUE;
	if ( c == '.' || c == ' ' || c == '!' || c == '_' ||
	     c == ';' || c == '(' || c == ')' || c == '-' ||
		 c == '+' || c == '%' || c == '=' )
	{
		return TRUE;
	}
	DEBUG_PRINT(("bad symol - '%c'\n", c));	
	return FALSE;
}