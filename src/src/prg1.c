/*
	Project: ProcessString
	Functional area: Project start point
	Author: Tyurin Dima
	Contact data: tyurin94@gmail.com
	Creation: 21.02.2013
*/

#include "S:\h\util.h"
#include "S:\h\stmachine.h"
	
int main(int argc, char* argv[])
{
	DEBUG_SYSTEM(("cls"));
	DEBUG_PRINT(("Starting program prg1\n"));

	struct SysData sysData;
	init(&sysData);
	sysData.argc = argc;
	sysData.argf = argv[1];
	
	enum StCodes cur_state = ENTRY_STATE;
    enum RetCodes rc;
	PMachineFunc pFunc; 
	
    for (;;) 
	{
		DEBUG_PRINT(("---------------------------\n"));
		DEBUG_PRINT(("current_state = %s\n", getStTitle(cur_state)));
    
		pFunc = find_state_func(cur_state);
		if (!pFunc) 
		{
			DEBUG_PRINT(("pFunc is NULL\n"));		
		}
		
		rc = pFunc(&sysData);
		DEBUG_PRINT(("rc = %s\n", getRetTitle(rc)));		
        
		if (EXIT_STATE == cur_state)
            break;
        cur_state = find_transitions(cur_state, rc);
	}

	DEBUG_PRINT(("---------------------------\n"));
	DEBUG_PRINT(("return %d\n", sysData.retVal));		
	DEBUG_SYSTEM(("pause"));
    return sysData.retVal;		
}