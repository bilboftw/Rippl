/************************************************************************/
/* Rippl Interface Main Window                                          */
/************************************************************************/

// Includes
#include <windows.h>

#include "resource.h"

#include "ri_window.h"

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

	// Create Window
	MakeWindow();
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
	_wcxClass.hbrBackground =	COLOR_WINDOWTEXT+1;
	_wcxClass.lpszClassName =	NULL;
	_wcxClass.lpszClassName =	"RipplMain";
	_wcxClass.hIconSm =			NULL;
}

void RIWindow::RegClass()
{
	// Register Class
	_aAtom = RegisterClassEx(&_wcxClass);

	// Check

}

void RIWindow::MakeWindow()
{
	
}

void RIWindow::KillWindow()
{

}