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

// Using Gdiplus
using namespace Gdiplus;

// Static Defines
Splash* Splash::_lpSplash = NULL;
HINSTANCE Splash::_hinstMainInst = NULL;

static Gdiplus::ImageAttributes iaAttr;
static Gdiplus::ColorMatrix ClrMatrix = { 
	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

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
	// Check state
	if(_ssState != SPLASH_HIDDEN) return;

	// Set state
	_ssState = SPLASH_SHOWING;

	// Show the window
	ShowWindowAsync(_hwndWindow, SW_SHOWNORMAL);

	// Update the window
	UpdateWindow(_hwndWindow);

	// Set up initial positions
	_pngMainLogo->frcDest->X = (_oGrphInf.szSize.cx / 2) - (_pngMainLogo->frcDest->Width / 2);

	// Setup Tween information
	Tween* tMainFade = new Tween(600, 0, &rTweenCB, EOUT);
	tMainFade->uArg.iInt = SPLASHANIM_FADE;

	// Send them on their way
	TweenEngine::Get()->Add(tMainFade);
}

void Splash::rTweenCB(Tween* lpTween, R_TWEEN_CB_MSG code)
{
	// Switch callback type
	switch(code)
	{
	case PROGRESS:
		// Switch stage
		switch(lpTween->uArg.iInt)
		{
		case SPLASHANIM_FADE:
			// Set alpha of main logo
			Get()->_pngMainLogo->fAlpha = (float)lpTween->dEasedValue;
			break;
		}

		// Break
		break;
	case FINISH:
		// Check if it's the last fade
		if(Get()->_ssState == SPLASH_SHOWING && lpTween->uArg.iInt == SPLASHANIM_NATFADE)
			// Set state
			Get()->_ssState = SPLASH_VISIBLE;
		else if(Get()->_ssState == SPLASH_HIDING && lpTween->uArg.iInt == SPLASHANIM_FADE)
			// Set state
			Get()->_ssState = SPLASH_HIDDEN;
		break;
	}
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
	_oGrphInf.szSize.cx = _rcSize.right;
	_oGrphInf.szSize.cy = _rcSize.bottom;

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

	// Set up graphics
	_oGrphInf.hdcScreen = GetDC(NULL);
	_oGrphInf.hdcMem = CreateCompatibleDC(_oGrphInf.hdcScreen);
	_oGrphInf.hBmp = CreateCompatibleBitmap(_oGrphInf.hdcScreen, _oGrphInf.szSize.cx, _oGrphInf.szSize.cy);
	_oGrphInf.hBmpOld = (HBITMAP)SelectObject(_oGrphInf.hdcMem, _oGrphInf.hBmp);
	_oGrphInf.graphics = new Gdiplus::Graphics(_oGrphInf.hdcMem);

	_oGrphInf.graphics->SetSmoothingMode((Gdiplus::SmoothingMode)0x04); // SmoothingModeAntiAlias8x4

	memset(&_oGrphInf.blend, 0, sizeof(_oGrphInf.blend));
	_oGrphInf.blend.BlendOp = AC_SRC_OVER;
	_oGrphInf.blend.SourceConstantAlpha = 255;
	_oGrphInf.blend.AlphaFormat = AC_SRC_ALPHA;

	_oGrphInf.ptSrcPos.x = 0;
	_oGrphInf.ptSrcPos.y = 0;

	// Start drawing thread
	hDrawThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&SplashGraphicsDrawEP, NULL, NULL, NULL);
}

DWORD Splash::SplashGraphicsDrawEP(PVOID arg)
{
	// Get pointer (less overhead)
	Splash* s = Get();

	// Loop!
	while(true)
	{
		// Clear graphics
		s->_oGrphInf.graphics->Clear((Gdiplus::Color)0);

		// Draw PNGs
		s->DrawPNG(Get()->_pngMainLogo);

		// Call UpdateLayeredWindow
		UpdateLayeredWindow(s->_hwndWindow, s->_oGrphInf.hdcScreen, NULL, &s->_oGrphInf.szSize, s->_oGrphInf.hdcMem, &s->_oGrphInf.ptSrcPos, 0, &s->_oGrphInf.blend, ULW_ALPHA);

		// Sleep!
		Sleep(1000 / R_SPLASH_DRAW_FPS);
	}

	// Return 
	return 0;
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

void Splash::DrawPNG(PNG* lpPNG)
{
	// Check alpha
	if(lpPNG->fAlpha <= 0.0f) return;

	// Set alpha
	ClrMatrix.m[3][3] = lpPNG->fAlpha;
	Gdiplus::ImageAttributes iaAttr;
	iaAttr.SetColorMatrix(&ClrMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	
	// Draw
	_oGrphInf.graphics->DrawImage(lpPNG->GetImage(), *lpPNG->frcDest, lpPNG->frcSrc->X, lpPNG->frcSrc->Y, lpPNG->frcSrc->Width, lpPNG->frcSrc->Height, Gdiplus::UnitPixel, &iaAttr);
	_oGrphInf.graphics->Flush(); // If this doesn't work, try putting this in the thread EP
}

Splash::~Splash()
{
	// Kill thread
	TerminateThread(hDrawThread, 0);

	// Clean up graphics
	delete _oGrphInf.graphics;
	SelectObject(_oGrphInf.hdcMem, _oGrphInf.hBmpOld);	
	DeleteObject(_oGrphInf.hBmp);
	DeleteDC(_oGrphInf.hdcMem);
	ReleaseDC(NULL, _oGrphInf.hdcScreen);

	// Delete PNG objects
	delete _pngMainLogo;

	// Set pointer to NULL
	Splash::_lpSplash = NULL;
}