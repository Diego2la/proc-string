/*
	Project: ProcessString
	Functional area: Implimentaion logic of application as state machine
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 24.02.2013
*/

#ifndef _ST_MACHINE_INCLUDED_
#define _ST_MACHINE_INCLUDED_

#include "S:\h\util.h"
#include "S:\h\sysdata.h"

/* all machine states */
enum StCodes 
{
	ST_GET_ARGS           , 
	ST_CHOOSE_STRING      , 
	ST_ENTER_FILE_NAME    ,
	ST_CHECK_ARGS         , 
	ST_PREPARE_STRING     ,
	ST_ENTER_STRING       ,
	ST_PROCESS_STRING     ,
	ST_TO_MUCH_ERRORS     ,
	ST_SRC_FILE_NOT_FOUND ,
	ST_WRITE_FILE         ,
	ST_PRINT_RES          ,
	ST_RETURN_1           ,
	ST_RETURN_0           ,
	ST_EXIT_CODE          ,	
		
	ST_COUNT
};
const char* getStTitle(int state);


/* call functin for every machine state */

/* function choose input type*/
int get_args           (struct SysData* data);

/* resiving user command */
int choose_string      (struct SysData* data);

/* read filename with available symbols from stdin */
int enter_file_name    (struct SysData* data);

/* if arg not NULL this function check file extension
	and trys to open file for reading */
int check_args         (struct SysData* data);

/* read string from file and deleate bad symbols */
int prepare_string     (struct SysData* data);

/* get string from stdin and check it */
int enter_strig        (struct SysData* data);

/* main application logic */
int process_string     (struct SysData* data);

/* check error attempts count while reading string from stdin */
int to_much_errors     (struct SysData* data);

/* console message */
int src_file_not_found (struct SysData* data);

/* try to create file and write resualt to file */
int write_file         (struct SysData* data);

/* printf program resualt on stdin */
int print_res          (struct SysData* data);

/* functions save ret befor exit */
int return_1           (struct SysData* data);
int return_0           (struct SysData* data);

/* empty exit funcion */
int exit_code          (struct SysData* data);

/* functions return values */
enum RetCodes
{ 
	RET_DEFAULT  ,
	RET_CONSOLE  ,
	RET_FILE     ,
	RET_TRUE     ,
	RET_FALSE    ,
	RET_SYM_1    ,
	RET_SYM_2    ,
	RET_RETURN_0 ,
	RET_RETURN_1 ,
	
	RET_COUNT
};
const char* getRetTitle(int ret);

typedef int (*PMachineFunc)(struct SysData*);
struct ActionCell
{
	int          state;
	PMachineFunc action;
};

struct Transition 
{
    enum StCodes  src;
    enum RetCodes ret;
    enum StCodes  dst;
};

#define ENTRY_STATE ST_GET_ARGS
#define EXIT_STATE ST_EXIT_CODE

PMachineFunc find_state_func(int state);
int find_transitions(int src, int ret);

int clearStdin();

#endif /*_ST_MACHINE_INCLUDED_*/