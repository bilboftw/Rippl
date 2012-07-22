/************************************************************************/
/* Rippl Interface Main Window                                          */
/************************************************************************/

// Includes
#include <windows.h>

#include "resource.h"
#include "Macros.h"

#include "ri_window.h"
#include "strmgr.h"

// Static Defines
RIWindow* RIWindow::Inst = NULL;

void RIWindow::Init(HINSTANCE hinst)
{
	// Create new instance
	Inst = new RIWindow(hinst);
}

void RIWindow::Destroy()
{
	// Delete object
	delete Inst;

	// Set to NULL
	Inst = NULL;
}

RIWindow::RIWindow(HINSTANCE hinst)
{
	// Store hInstance
	_hInst = hinst;

	// Setup class
	SetupClass();

	// Register class
	RegClass();

	// Create window
	MakeWindow();

	// Show window
	Show();
}

LRESULT RIWindow::WinMsgHandler(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	// Return default
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

RIWindow::~RIWindow()
{
	// Unregister class
	UnregisterClass(_wcxClass.lpszClassName, _hInst);

	// Destroy Window
	KillWindow();
}

void RIWindow::SetupClass()
{
	// Zero out class
	memset(&_wcxClass, 0, sizeof(_wcxClass));

	// Set up class members
	_wcxClass.cbSize =			sizeof(_wcxClass);
	_wcxClass.style =			CS_DBLCLKS |				// Enable double-clicks
								CS_HREDRAW | CS_VREDRAW;	// Forces re-draw on resize
	_wcxClass.lpfnWndProc =		(WNDPROC)&WinMsgHandler;
	_wcxClass.hInstance =		_hInst;
	_wcxClass.hIcon =			LoadIcon(_hInst, MAKEINTRESOURCE(IDI_ICON1));
	_wcxClass.hCursor =			LoadCursor(NULL, IDC_CROSS);
	_wcxClass.hbrBackground =	(HBRUSH)(COLOR_WINDOWTEXT+1);
	_wcxClass.lpszMenuName =	NULL;
	_wcxClass.lpszClassName =	"RipplMain";
	_wcxClass.hIconSm =			NULL;
}

void RIWindow::RegClass()
{
	// Register Class
	_aAtom = RegisterClassEx(&_wcxClass);

	// Check and log
	if(_aAtom == 0)
		LOGE("Could not register RIWindow class: %u", GetLastError());
}

void RIWindow::MakeWindow()
{
	// Create window
	_hwndWindow = CreateWindowExW(	WS_EX_ACCEPTFILES |				// Accepts files
										WS_EX_COMPOSITED |			// Double-buffer drawing (Btm->Top)
										WS_EX_LAYERED |				// Layered window
										WS_EX_WINDOWEDGE,
									(LPCWSTR)_aAtom,
									SGETSTRING(R_WIN_CAPTION),
									_wcxClass.style,
									0, 0,							// Update these values with values stored in
									1024, 768,						//	state files
									NULL,
									NULL,
									_hInst,
									NULL
									);

	// Check
	if(_hwndWindow == NULL)
		// Log
		LOGW("Could not open main RI window: %u", GetLastError());
}

void RIWindow::KillWindow()
{
	// Destroy window
	DestroyWindow(_hwndWindow);
}

void RIWindow::Show()
{
	// Show window
	if(ShowWindow(_hwndWindow, SW_SHOWDEFAULT) == FALSE)
		// Log
		LOGW("Could not show main RI window: %u", GetLastError());
}

void RIWindow::Hide()
{
	// Hide window
	if(ShowWindow(_hwndWindow, SW_HIDE) == FALSE)
		// Log
		LOGW("Could not hide main RI window: %u", GetLastError());
}