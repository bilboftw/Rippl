/************************************************************************/
/* Rippl Process/Application Control Functions                          */
/************************************************************************/

// Includes
#include <windows.h>

// Static Defines
static HANDLE hwndMainThread;

/**
 * Initializes Resources
 *	This MUST be called from the main thread to properly
 *	set up the system!
 */
void InitResources()
{
	// Store handle to current thread
	hwndMainThread = GetCurrentThread();
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
void TerminateProgram(int iExitCode)
{
	// Release Resources
	ReleaseResources();

	// Terminate Main Thread
	TerminateThread(hwndMainThread, iExitCode);
}