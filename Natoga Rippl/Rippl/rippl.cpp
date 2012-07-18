/************************************************************************/
/* Rippl Process/Application Control Functions                          */
/************************************************************************/

// Includes
#ifdef _WINDOWS
#include <windows.h>
#endif

// Static Defines
#ifdef _WINDOWS
static HANDLE hwndMainThread;
#endif

/**
 * Initializes Resources
 *	This MUST be called from the main thread to properly
 *	set up the system!
 */
void InitResources()
{
	// Store handle to current thread
#ifdef _WINDOWS
	hwndMainThread = GetCurrentThread();
#endif
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