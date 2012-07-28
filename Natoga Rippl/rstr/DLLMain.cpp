/************************************************************************/
/* RIPPLE Studio                                                        */
/*                                                                      */
/*    String Library                                                    */
/*    Holds the strings used by the Win32 System.                       */
/************************************************************************/

// Includes
#include <Windows.h>

#include "ROutput.h"
#include "iStringMgr.h"

#include "strmgr.h"

// Static Defines
bool bLoaded = false;

// External Header
extern "C" __declspec(dllexport) iStringMgr* __stdcall MGS(ROutputHandler** rohOutputHandler)
{
	// Store output handler
	rohHandler = rohOutputHandler;

	// Return!
	return StringMgr::Get();
}

// DLLMain Entry Point - Inits the string system
BOOL __stdcall DllMain(HINSTANCE hDllHandle, DWORD dwReason, LPVOID lpreserved)
{
	// Check/set bLoaded
	if(bLoaded)
		return TRUE;

	// Set bLoaded
	bLoaded = true;
	
	// Init system
	StringMgr::Init(hDllHandle);

	// Return TRUE
	return TRUE;
}