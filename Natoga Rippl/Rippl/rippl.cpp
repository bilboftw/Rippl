/************************************************************************/
/* Rippl Process/Application Control Functions                          */
/************************************************************************/

// Includes
#include <windows.h>
#include <GdiPlus.h>

#include "resource.h"
#include "Macros.h"

#include "r_str.h"
#include "tween_engine.h"
#include "splash.h"
#include "ri_window.h"
#include "ri_sdl.h"
#include "r_themes.h"
#include "ROutput.h"

// Prototype Definitions
void LoadStringLib();

// Static / Extern Defines
static HANDLE hwndMainThread;
extern iStringMgr* lpRStrMgr = NULL;

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

	// Setup Default Output
	ROutput::Init();

	// Load Strings
	LoadStringLib();

	// Initialize GDI+
	Gdiplus::GdiplusStartup(&stGdiPlusI.lpToken, &stGdiPlusI.gdiplusStartupInput, NULL);

	// Init splash
	Splash::Init(hinstInst);

	// Show splash screen
	Splash::Get()->ShowWait();
	
	// Load Configuration
	Splash::Get()->UpdateStatus(SGETSTRING(R_LOADMSG_CONFIG));
	RTheme::Init();				// - Themes

	// Set up SDL
	Splash::Get()->UpdateStatus(SGETSTRING(R_LOADMSG_SDL));
	RSDL::Init();

	// Set up main interface
	Splash::Get()->UpdateStatus(SGETSTRING(R_LOADMSG_INTERFACE));
	RIWindow::Init();

	// Set up components
	Splash::Get()->UpdateStatus(SGETSTRING(R_LOADMSG_COMPONENTS));

	// - Redraw Window
	RIWindow::Inst->Redraw();

	// Completed~!
	Splash::Get()->UpdateStatus(SGETSTRING(R_LOADMSG_COMPLETE));
	Splash::Get()->HideWait();
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

	// Unload Config
	RTheme::Unload();			// - Themes

	// Unload Output
	ROutput::Uninstall();
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

void LoadStringLib()
{
	// Initialize Strings
	lpRStrMgr = MGS(&ROutput::Handler);
}