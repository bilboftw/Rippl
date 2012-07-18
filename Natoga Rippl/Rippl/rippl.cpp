/************************************************************************/
/* Rippl Process/Application Control Functions                          */
/************************************************************************/

// Includes
#include <windows.h>

#include "strmgr.h"
#include "tween_engine.h"
#include "splash.h"

// Static Defines
static HANDLE hwndMainThread;

/**
 * Initializes Resources
 *	This MUST be called from the main thread to properly
 *	set up the system!
 */
void InitResources(HINSTANCE hinstInst)
{
	// Store handle to current thread
	hwndMainThread = GetCurrentThread();

	// Initialize Strings
	StringMgr::Init(hinstInst);

	// Show splash screen
	Splash::Get()->ShowWait();
}

/**
 * Released system resources
 */
void ReleaseResources()
{
	
}

/**
 * Terminates the program with a certain code
 */
void TerminateRippl(int iExitCode)
{
	// Release Resources
	ReleaseResources();

	// Terminate Main Thread
	TerminateProcess(GetCurrentProcess(), iExitCode);
}