/*
	Project: ProcessString
	Functional area: auxiliary stuct and functions for state machine
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 24.02.2013
*/

#ifndef _SYS_DATA_INCLUDED_
#define _SYS_DATA_INCLUDED_

#include "S:\h\util.h"

enum IoType
{ 
	IO_UNKNOWN ,
	IO_CONSOLE ,
	IO_FILE 
};

struct SysData
{
	enum IoType ioType;
	FILE* input;
	FILE* output;
	char str[MAX_STRING_SIZE + 1];
	char fileName[MAX_FILE_NAME_SIZE + 1];
	int erCount;
	int retVal;
	
	int argc;
	/* first console arg */
	char* argf; 
};

void init(struct SysData* data);

#endif /*_SYS_DATA_INCLUDED_*/