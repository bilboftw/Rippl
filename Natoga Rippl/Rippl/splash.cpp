/************************************************************************/
/* Splash Screen Implementation                                         */
/************************************************************************/

// Includes
#include <windows.h>
#include <assert.h>
#include <GdiPlus.h>

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
		
	}
}

void Splash::SetupShowTweenInfo()
{
	// Create tween objects
	_twnFade = new Tween();
	_twnFade->lDuration = 600;
	_twnFade->cbOnEvent = &rTweenCB;
}

Splash::Splash()
{
	// Set initial states
	_ssState = SPLASH_HIDDEN;
	_ssAnimState = SPLASHANIM_FADE;

	// Load bitmaps
	_pngMainLogo = new PNG(R_PNG_SPLASH_MAIN_LOGO);

	// Check
	if(_pngMainLogo == NULL)
		LOGW("Could not load bitmap file: %u", GetLastError());


	// Set up class
	_wcWClass.cbSize = sizeof(WNDCLASSEX);
	_wcWClass.style = 0;
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

	// Set up window's bitmap drawing information
	memset(&_oGrphInf.bmpWinInformation, 0, sizeof(_oGrphInf.bmpWinInformation));
	_oGrphInf.bmpWinInformation.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	_oGrphInf.bmpWinInformation.bmiHeader.biWidth = _rcSize.right;
	_oGrphInf.bmpWinInformation.bmiHeader.biHeight = -(_rcSize.bottom);
	_oGrphInf.bmpWinInformation.bmiHeader.biPlanes = 1;
	_oGrphInf.bmpWinInformation.bmiHeader.biBitCount = 32;
	_oGrphInf.bmpWinInformation.bmiHeader.biCompression = BI_RGB;
	_oGrphInf.bmpWinInformation.bmiHeader.biSizeImage = 0;
	_oGrphInf.bmpWinInformation.bmiHeader.biXPelsPerMeter = 0;
	_oGrphInf.bmpWinInformation.bmiHeader.biYPelsPerMeter = 0;
	_oGrphInf.bmpWinInformation.bmiHeader.biClrImportant = 0;
	_oGrphInf.bmpWinInformation.bmiHeader.biClrUsed = 0;

	// Log
	LOGD("Spawning window at %u %u", wx, wy);

	// Create Window
	_hwndWindow = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST,
					(LPCWSTR)_atomWinAtom,
					StringMgr::Get()->GetString(R_SPLASH_TITLE),
					WS_VISIBLE | WS_POPUP,
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

	// Create DC
	_oGrphInf.canvasHDC = GetDC(_hwndWindow);

	// Create drawing 'canvas'
	_oGrphInf.lpBits = NULL;
	_oGrphInf.bmpCanvas = CreateDIBSection(_oGrphInf.canvasHDC, &_oGrphInf.bmpWinInformation, DIB_RGB_COLORS, &_oGrphInf.lpBits, NULL, 0);

	// Create graphics object
	_oGrphInf.graphics = new Gdiplus::Graphics(_oGrphInf.canvasHDC);

	// Attempt to draw
	DrawPNG(_pngMainLogo, 0, 0);
}

LRESULT Splash::SplashProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Switch message
	switch(msg)
	{
	case WM_QUIT:
		// Log and terminate
		LOGI("Exiting prematurely");
		TerminateRippl(1);
		break;
	}

	// Handle Unhandled Messages
	return DefWindowProc(hWindow, msg, wParam, lParam);
}

void Splash::DrawPNG(PNG* lpPNG, int x, int y)
{
	LOGD("Drawing bitmap!");
	
	HDC hdcMem = CreateCompatibleDC(_oGrphInf.canvasHDC);

	// Select
	HBITMAP bmpOld = (HBITMAP)SelectObject(hdcMem, _oGrphInf.bmpCanvas);

	Gdiplus::Color trans(0, 0, 0, 0);
	_oGrphInf.graphics->Clear(trans);

	_oGrphInf.graphics->DrawImage(lpPNG->GetImage(), x, y);

	_oGrphInf.graphics->Flush();

	SIZE szSize = {_oGrphInf.bmpWinInformation.bmiHeader.biWidth, _oGrphInf.bmpWinInformation.bmiHeader.biHeight};

	// Setup drawing location
	POINT ptLoc = {0, 0};
	POINT ptSrc = {0, 0};

	// Set up alpha blending
	BLENDFUNCTION blend = {0};
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;
	blend.BlendFlags = 0;
	
	// Update
	if(UpdateLayeredWindow(_hwndWindow, _oGrphInf.canvasHDC, NULL, NULL, hdcMem, &ptLoc, RGB(0, 0, 0), &blend, ULW_ALPHA) == FALSE)
		LOGE("Could not update layered window: %u", GetLastError());

	// Delete temp objects
	SelectObject(hdcMem, bmpOld);
	DeleteObject(hdcMem);
	DeleteDC(hdcMem);
}

Splash::~Splash()
{
	// Delete PNG objects
	delete _pngMainLogo;

	// Set pointer to NULL
	Splash::_lpSplash = NULL;
}