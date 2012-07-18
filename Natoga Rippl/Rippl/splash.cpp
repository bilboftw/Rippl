/************************************************************************/
/* Splash Screen Implementation                                         */
/************************************************************************/

// Includes
#include <windows.h>
#include <assert.h>

#include "Macros.h"

#include "rippl.hpp"
#include "splash.h"
#include "strmgr.h"
#include "resource.h"
#include "tween_engine.h"

// Static Defines
Splash* Splash::_lpSplash = NULL;
HINSTANCE Splash::_hinstMainInst = NULL;

void Splash::Init(HINSTANCE hinstInst)
{
	// Store HInstance
	_hinstMainInst = hinstInst;
}

Splash* Splash::Get()
{
	// Create if not created
	if(_lpSplash == NULL)
		_lpSplash = new Splash();

	// Return
	return _lpSplash;
}

void Splash::Destroy()
{
	// TODO: Hide and wait

	// Delete Object
	delete _lpSplash;
}

void Splash::Hide()
{
	// Hide the window
	ShowWindowAsync(_hwndWindow, SW_HIDE);
}

void Splash::HideWait()
{
	// Call Hide
	Hide();

	// TODO: Wait
}

void Splash::Show()
{
	// Show the window
	ShowWindowAsync(_hwndWindow, SW_SHOWNORMAL);

	// Update the window
	UpdateWindow(_hwndWindow);

	// Setup Tween information
	SetupShowTweenInfo();

	// Send them on their way
	TweenEngine::Get()->Add(_twnFade);
}

void Splash::ShowWait()
{
	// Call Show
	Show();

	// TODO: Wait
}

void Splash::UpdateStatus(const char* szString)
{
	
}

void Splash::rTweenCB(Tween* lpTween, R_TWEEN_CB_MSG code)
{
	// If we've made a nominal progress...
	if(code == PROGRESS)
	{
		LOGD("Progress %u", lpTween->cEasedValue);
	}
}

void Splash::SetupShowTweenInfo()
{
	// Create tween objects
	_twnFade = new Tween();
	_twnFade->lDuration = 600;
}

Splash::Splash()
{
	// Set initial states
	_ssState = SPLASH_HIDDEN;
	_ssAnimState = SPLASHANIM_FADE;

	// Set up class
	_wcWClass.cbSize = sizeof(WNDCLASSEX);
	_wcWClass.style = CS_HREDRAW | CS_VREDRAW;
	_wcWClass.lpfnWndProc = (WNDPROC)&SplashProc;
	_wcWClass.cbClsExtra = 0;
	_wcWClass.cbWndExtra = 0;
	_wcWClass.hInstance = _hinstMainInst;
	_wcWClass.hIcon = LoadIcon(_hinstMainInst, MAKEINTRESOURCE(IDI_ICON1));
	_wcWClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wcWClass.hbrBackground = (HBRUSH)0;
	_wcWClass.lpszClassName = "RSplashScreen";
	_wcWClass.lpszMenuName = "MainMenu";
	_wcWClass.hIconSm = NULL;

	// Register Class
	_atomWinAtom = RegisterClassEx(&_wcWClass);

	// Check
	if(_atomWinAtom == 0)
	{
		// Warn and break
		LOGE("Could not register splash window class: %u", GetLastError());
		assert(false);
		return;
	}

	// Determine Size
	//	Change this value according to the image size
	_rcSize.right = 931;
	_rcSize.bottom = 547;

	// Get desktop size
	WINDOWINFO winInf;
	GetWindowInfo(GetDesktopWindow(), &winInf);

	// Determine position
	_rcSize.left = 0;
	_rcSize.top = 0;
	int wx = (winInf.rcWindow.right / 2) - (_rcSize.right / 2);
	int wy = (winInf.rcWindow.bottom / 2) - (_rcSize.bottom / 2);

	// Log
	LOGD("Spawning window at %u %u", wx, wy);


	// Create Window
	_hwndWindow = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE,
					(LPCWSTR)_atomWinAtom,
					StringMgr::Get()->GetString(R_SPLASH_TITLE),
					WS_DLGFRAME | WS_VISIBLE,
					wx,
					wy,
					_rcSize.right,
					_rcSize.bottom,
					NULL,
					NULL,
					_hinstMainInst,
					NULL
					);

	// Check
	if(_hwndWindow == NULL)
	{
		// Error, break and return
		LOGE("Could not create splash screen window: %u", GetLastError());
		assert(false);
		return;
	}else
	{
		// Log and invalidate
		LOGD("Created splash window!");
		InvalidateRect(_hwndWindow, &_rcSize, TRUE);
	}
}

LRESULT Splash::SplashProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Switch message
	switch(msg)
	{
	case WM_PAINT:
		

		// Update (again)
		UpdateWindow(hWindow);
		break;
	case WM_QUIT:
		// Log and terminate
		LOGI("Exiting prematurely");
		TerminateRippl(1);
		break;
	}

	// Handle Unhandled Messages
	return DefWindowProc(hWindow, msg, wParam, lParam);
}

Splash::~Splash()
{
	// Set pointer to NULL
	Splash::_lpSplash = NULL;
}