/*
	Project: ProcessString
	Functional area: auxiliary stuct and functions for state machine
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 24.02.2013
*/

#include "S:\h\sysdata.h"

void init(struct SysData* data)
{
	data->ioType = IO_UNKNOWN;
	data->input  = NULL;
	data->output = NULL;
	data->str[0] = '\0';
	data->fileName[0] ='\0';
	data->erCount = 0;
	data->retVal = 3;
	data->argc = 0;
	data->argf = NULL;
}
