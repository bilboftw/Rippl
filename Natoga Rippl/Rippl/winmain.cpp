/************************************************************************/
/* WinMain Function                                                     */
/*   Windows only!                                                      */
/************************************************************************/

// Includes
#include <windows.h>

#include "Macros.h"

#include "rippl.hpp"
#include "resource.h"
#include "strmgr.h"
#include "tween_engine.h"

/**
 * WinMain Function
 *	Main Windows program entry point
 */
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Initialize Resources
	InitResources(hInstance);
	
	// DEBUG: Message Box
	//MessageBoxW(NULL, StringMgr::Get()->GetString(R_DEBUG_MSG), StringMgr::Get()->GetString(R_TITLE), MB_OK);

	while(true){Sleep(5000);}
	
	// Release Resources
	ReleaseResources();

	// Return Success
	return 0;
}