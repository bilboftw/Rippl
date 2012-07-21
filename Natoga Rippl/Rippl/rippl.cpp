/************************************************************************/
/* Rippl Process/Application Control Functions                          */
/************************************************************************/

// Includes
#include <windows.h>
#include <GdiPlus.h>

#include "resource.h"

#include "strmgr.h"
#include "tween_engine.h"
#include "splash.h"

// Static Defines
static HANDLE hwndMainThread;

// GDIPlus Information
struct R_GDI_PLUS_INFO
{
	ULONG_PTR lpToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
} static stGdiPlusI;

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

	// DEBUG: Message Box
	MessageBoxW(NULL, StringMgr::Get()->GetString(R_DEBUG_MSG), StringMgr::Get()->GetString(R_TITLE), MB_OK);

	// Initialize GDI+
	Gdiplus::GdiplusStartup(&stGdiPlusI.lpToken, &stGdiPlusI.gdiplusStartupInput, NULL);

	// Init splash
	Splash::Init(hinstInst);

	// Show splash screen
	Splash::Get()->ShowWait();
}

/**
 * Released system resources
 */
void ReleaseResources()
{
	// Destroy Splash
	Splash::Get()->Destroy();

	// De-init GDI+
	Gdiplus::GdiplusShutdown(stGdiPlusI.lpToken);
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