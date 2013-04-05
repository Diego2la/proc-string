/*
   Project: ProcessString
   Functional area: Implimentaion logic of application as state machine
   Author: Tyurin Dima
   Contact data: tyurin94@gmail.com
   Creation: 24.02.2013
*/

#include "S:\h\stmachine.h"

/* direct connection between StCodes and functions */
struct ActionCell actionCell[] =
{
   { ST_GET_ARGS          , get_args           },
   { ST_CHOOSE_STRING     , choose_string      },
   { ST_ENTER_FILE_NAME   , enter_file_name    },
   { ST_CHECK_ARGS        , check_args         },
   { ST_PREPARE_STRING    , prepare_string     },
   { ST_ENTER_STRING      , enter_strig        },
   { ST_PROCESS_STRING    , process_string     },
   { ST_TO_MUCH_ERRORS    , to_much_errors     },
   { ST_SRC_FILE_NOT_FOUND, src_file_not_found },
   { ST_WRITE_FILE        , write_file         },
   { ST_PRINT_RES         , print_res          },
   { ST_RETURN_1          , return_1           },
   { ST_RETURN_0          , return_0           },
   { ST_EXIT_CODE         , exit_code          }
};

struct Transition state_transitions[] =
{
   { ST_GET_ARGS           , RET_CONSOLE  , ST_CHOOSE_STRING      }, 
   { ST_GET_ARGS           , RET_FILE     , ST_CHECK_ARGS         }, 
   { ST_GET_ARGS           , RET_FALSE    , ST_RETURN_1           }, 
   { ST_CHOOSE_STRING      , RET_FALSE    , ST_CHOOSE_STRING      },
   { ST_CHOOSE_STRING      , RET_SYM_2    , ST_ENTER_FILE_NAME    },
   { ST_CHOOSE_STRING      , RET_SYM_1    , ST_ENTER_STRING       },
   { ST_ENTER_FILE_NAME    , RET_TRUE     , ST_CHECK_ARGS         },
   { ST_ENTER_FILE_NAME    , RET_FALSE    , ST_SRC_FILE_NOT_FOUND },
   { ST_CHECK_ARGS         , RET_TRUE     , ST_PREPARE_STRING     },
   { ST_CHECK_ARGS         , RET_FALSE    , ST_SRC_FILE_NOT_FOUND },
   { ST_PREPARE_STRING     , RET_DEFAULT  , ST_PROCESS_STRING     },
   { ST_PREPARE_STRING     , RET_FALSE    , ST_RETURN_1           },
   { ST_ENTER_STRING       , RET_TRUE     , ST_PROCESS_STRING     },
   { ST_ENTER_STRING       , RET_FALSE    , ST_TO_MUCH_ERRORS     },
   { ST_PROCESS_STRING     , RET_CONSOLE  , ST_PRINT_RES          },
   { ST_PROCESS_STRING     , RET_FILE     , ST_WRITE_FILE         },
   { ST_PROCESS_STRING     , RET_FALSE    , ST_RETURN_1           },
   { ST_TO_MUCH_ERRORS     , RET_FALSE    , ST_ENTER_STRING       },
   { ST_TO_MUCH_ERRORS     , RET_RETURN_1 , ST_RETURN_1           },
   { ST_SRC_FILE_NOT_FOUND , RET_DEFAULT  , ST_RETURN_1           },
   { ST_WRITE_FILE         , RET_RETURN_1 , ST_RETURN_1           },
   { ST_WRITE_FILE         , RET_RETURN_0 , ST_RETURN_0           },
   { ST_PRINT_RES          , RET_DEFAULT  , ST_RETURN_0           },
   { ST_RETURN_1           , RET_DEFAULT  , ST_EXIT_CODE          },
   { ST_RETURN_0           , RET_DEFAULT  , ST_EXIT_CODE          },
   /* end of array marker */
   { ST_COUNT              , RET_COUNT    , ST_COUNT              }
};


PMachineFunc find_state_func(int state)
{
   int i;
   for (i = 0; i < ST_COUNT; ++i)
   {
      if (actionCell[i].state == state)
         return actionCell[i].action;
   }
   DEBUG_PRINT(("state function not found\n"));
   return NULL;
}

int find_transitions(int src, int ret)
{
   int i = 0;
   while ( state_transitions[i].src != ST_COUNT )
   {
      if ( state_transitions[i].src == src && 
           state_transitions[i].ret == ret )
         return state_transitions[i].dst;
      ++i;
   }
   DEBUG_PRINT(("transmission not found state=%s, ret=%s\n",
      getStTitle(src), getRetTitle(ret) ));
   return ST_RETURN_1;
}

int get_args(struct SysData* data)
{
   if (data->argc >= 2)
   {
      assert(data->argf);
      if (strlen(data->argf) <= MAX_FILE_NAME_SIZE && noBadSymbols(data->argf) )
      {
         strcpy(data->fileName, data->argf);
         data->ioType = IO_FILE;
         DEBUG_PRINT(("io from file=%s\n", data->fileName));
         return RET_FILE;
      }
      else
      {
         printf("%s\n", MES_1_4);
         return RET_FALSE;
      }
   }

   DEBUG_PRINT(("io from console\n"));
   return RET_CONSOLE;
}

int choose_string(struct SysData* data)
{
   char c;
   printf("%s\n", MES_1_1);
   c = getchar();
   DEBUG_PRINT(("c = '%c'\n", c));
   if (isStdClear() == TRUE) 
   {
      if (c == '1')
      {
         data->ioType = IO_CONSOLE;
         return RET_SYM_1;
      }
      if (c == '2')
      {
         data->ioType = IO_FILE;
         return RET_SYM_2;
      }
   }
   return RET_FALSE;
}

int enter_file_name(struct SysData* data)
{
   int i = 0;
   char ch;
   DEBUG_PRINT(("trying to get file name\n"));
   printf("%s\n", MES_1_5);

   while ( (ch = getchar()) != '\n' && ch != EOF && i < MAX_FILE_NAME_SIZE )
   {
      DEBUG_PRINT(("ch = '%c'\n", ch));
      data->fileName[i] = (ch == '\n') ? '\0' : ch ;
      ++i;
   }
   data->fileName[i] = '\0';
   
   if ( ch == '\n' || ch == EOF )
   {
      DEBUG_PRINT(("resived str = \"%s\"\n", data->fileName));
      for (i = 0; i < strlen(data->fileName); ++i)
      {
         if ( checkSymbol(data->fileName[i]) == FALSE )
            return RET_FALSE;
      }
      return RET_TRUE;
   }
   else isStdClear();

   return RET_FALSE;
}

int check_args(struct SysData* data)
{
   char *fileName = data->fileName;
   assert( fileName != NULL );

   // reciving file extension             
   char* ext = strrchr(fileName, '.');
   ext = (ext && ext != fileName)
      ? ext : (fileName + strlen(fileName));

   DEBUG_PRINT(("ext=\"%s\"; templ=\"%s\"\n",
      ext, s_input_file_ext));

   // if extensions are equal
   if ( strcmp(ext, s_input_file_ext) == 0 )
   {
      data->input = fopen(fileName, "r");
      if (data->input != NULL)
         return RET_TRUE;
   }
   return RET_FALSE;
}

int prepare_string(struct SysData* data)
{
   int res;
   assert( data->input != NULL );
   if (fgets(data->str, MAX_STRING_SIZE + 1, data->input) != NULL)
   {
      DEBUG_PRINT(("data->str = %s\n", data->str));
      removeBadSymb(data->str);
      DEBUG_PRINT(("after removeBadSymb, data->str = %s\n", data->str));
      res = RET_DEFAULT;
   }
   else
   {
      printf("%s\n", MES_1_8);
      res = RET_FALSE;
   }
   fclose(data->input);
   return res;
}

int enter_strig(struct SysData* data)
{
   printf("%s\n", (data->erCount == 0) ? MES_1_2 : MES_1_3);

   int i = 0;
   char ch;
   while ( (ch = getchar()) != '\n' && ch != EOF && i < MAX_STRING_SIZE )
   {
      DEBUG_PRINT(("'%c'\n", ch));
      data->str[i] = (ch == '\n') ? '\0' : ch ;
      ++i;
   }
   data->str[i] = '\0';

   if ( ch == '\n' || ch == EOF )
   {
      DEBUG_PRINT(("valid string were inputed str = %s\n", data->str));
      for (i = 0; i < strlen(data->str); ++i)
      {
         if ( checkSymbol(data->str[i]) == FALSE )
            return RET_FALSE;
      }
      return RET_TRUE;
   }
   else isStdClear();

   return RET_FALSE;
}

int process_string(struct SysData* data)
{
   DEBUG_PRINT(("input string = %s\n", data->str));
   if (delStrTempl(data->str, s_string_template) == TRUE)
   {
      DEBUG_PRINT(("output string = %s\n", data->str));
      DEBUG_PRINT(("io Type is %u\n", data->ioType));
      switch(data->ioType)
      {
         case IO_CONSOLE : return RET_CONSOLE;
         case IO_FILE    : return RET_FILE;
         default         : 
         {
            DEBUG_PRINT(("unknown ioType %u\n", data->ioType));
            assert(FALSE);
         }
      }
   }
   else
   {
      // impossible with current process string logic 
      assert(FALSE);
   }
   return RET_FALSE;
}

int to_much_errors(struct SysData* data)
{
   ++data->erCount;
   DEBUG_PRINT(("error count = %d\n", data->erCount));
   if (data->erCount >= MAX_ERROR_READ_SRTING_COUNT)
   {
      printf("%s\n", MES_1_6);
      return RET_RETURN_1;
   }
   return RET_FALSE;
}

int src_file_not_found(struct SysData* data)
{
   printf("%s\n", MES_1_4);
   return RET_DEFAULT;
}

int write_file(struct SysData* data)
{
   int size = MAX_FILE_NAME_SIZE + strlen(s_output_file_ext) + 1;
   char newFile[size];
   newFile[0] = '\0';
   strcpy(newFile, data->fileName);

   DEBUG_PRINT(("inputfile = %s\n", data->fileName));
   DEBUG_PRINT(("newFile = %s\n", newFile));
   fillOutputFileName(newFile);
   DEBUG_PRINT(("outputfile = %s\n", newFile));
   int res;
   data->output = fopen(newFile, "w");
   if (data->output != NULL)
   {
      if (fputs(data->str, data->output) != EOF)
         res = RET_RETURN_0;
      fclose(data->output);
   }
   else
   {
      printf("%s\n", MES_1_7);
      res = RET_RETURN_1;
   }
   return res;
}

int print_res(struct SysData* data)
{
   printf("%s\n", data->str);
   return RET_DEFAULT;
}

int return_0(struct SysData* data)
{
   data->retVal = 0;
   return RET_DEFAULT;
}

int return_1(struct SysData* data)
{
   data->retVal = 1;
   return RET_DEFAULT;
}

int exit_code(struct SysData* data)
{
}

int isStdClear()
{
   DEBUG_PRINT(("... \n"));
   int ch;
   int count = 0;
   while ( (ch = getchar()) != '\n' && ch != EOF)
   {
      ++count;
   }
   return (count == 0) ? TRUE : FALSE ;
}

#ifdef DEBUG
const char* getStTitle(int state)
{
   switch(state)
   {
   case ST_GET_ARGS           : return "ST_GET_ARGS"           ;
   case ST_CHOOSE_STRING      : return "ST_CHOOSE_STRING"      ;
   case ST_ENTER_FILE_NAME    : return "ST_ENTER_FILE_NAME"    ;
   case ST_CHECK_ARGS         : return "ST_CHECK_ARGS"         ;
   case ST_PREPARE_STRING     : return "ST_PREPARE_STRING"     ;
   case ST_ENTER_STRING       : return "ST_ENTER_STRING"       ;
   case ST_PROCESS_STRING     : return "ST_PROCESS_STRING"     ;
   case ST_TO_MUCH_ERRORS     : return "ST_TO_MUCH_ERRORS"     ;
   case ST_SRC_FILE_NOT_FOUND : return "ST_SRC_FILE_NOT_FOUND" ;
   case ST_WRITE_FILE         : return "ST_WRITE_FILE"         ;
   case ST_PRINT_RES          : return "ST_PRINT_RES"          ;
   case ST_RETURN_1           : return "ST_RETURN_1"           ;
   case ST_RETURN_0           : return "ST_RETURN_0"           ;
   case ST_EXIT_CODE          : return "ST_EXIT_CODE"          ;
   case ST_COUNT              : return "ST_COUNT"              ;
   }
   return "UNKNOWN";
}

const char* getRetTitle(int ret)
{
   switch(ret)
   {
   case RET_DEFAULT  : return "RET_DEFAULT"  ;
   case RET_CONSOLE  : return "RET_CONSOLE"  ;
   case RET_FILE     : return "RET_FILE"     ;
   case RET_TRUE     : return "RET_TRUE"     ;
   case RET_FALSE    : return "RET_FALSE"    ;
   case RET_SYM_1    : return "RET_SYM_1"    ;
   case RET_SYM_2    : return "RET_SYM_2"    ;
   case RET_RETURN_0 : return "RET_RETURN_0" ;
   case RET_RETURN_1 : return "RET_RETURN_1" ;
   case RET_COUNT    : return "RET_COUNT"    ;
   }
   return "UNKNOWN";
}

#else
const char* getStTitle(int state)
{
   return "";
}
const char* getRetTitle(int ret)
{
   return "";
}
#endif
