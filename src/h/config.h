/*
	Project: laba1-14
	Functional area: Project configuration
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 22.02.2013
*/

#ifndef _CONFIG_INCLUDED_
#define _CONFIG_INCLUDED_

/* Availible build options:
   DEBUG, NDEBUG */
#define NDEBUG

/* for including <windows.h> 
   and using debug features */
#define WIN

#define TRUE 1
#define FALSE 0

extern const char* s_string_template;
extern const char* s_input_file_ext;
extern const char* s_output_file_ext;

/* String configuration */
#define MAX_STRING_SIZE 300
#define MAX_FILE_NAME_SIZE 247
#define MIN_COR_SYM 32
#define MAX_ERROR_READ_SRTING_COUNT 3

/* Program messages */
#define MES_1_1  "Choose string source: 1 - keyboard, 2 - file."
#define MES_1_2  "Enter string to process: "
#define MES_1_3  "Incorrect input, try again, enter string:"
#define MES_1_4  "Source file not found."
#define MES_1_5  "Enter source filename: "
#define MES_1_6  "Incorrect input, exited."
#define MES_1_7  "Error writing to file."
/* #define MES_1_8 Преобразованная строка. */ 
#define MES_1_9  "Input string is incompatible with algorithm."
#define MES_1_10 "Input text file is empty."

#endif /*_CONFIG_INCLUDED_*/
