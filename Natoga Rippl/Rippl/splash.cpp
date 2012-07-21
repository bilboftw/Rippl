/*****************************************************************************/
/* Splash Screen Implementation                                              */
/*   THANK YOU to Marc Gregoire for the only seemingly working               */
/*   implementation of UpdateLayeredWindow on the internet.                  */
/*                                                                           */
/*   http://www.nuonsoft.com/blog/2009/05/27/how-to-use-updatelayeredwindow/ */
/*****************************************************************************/

// Includes
#include <windows.h>
#include <GdiPlus.h>

#include "Macros.h"

#include "rippl.hpp"
#include "splash.h"
#include "strmgr.h"
#include "resource.h"
#include "tween_engine.h"

// Using Gdiplus
using namespace Gdiplus;

// Center Position Macro
#define CENTERF(obj, cont) (float)((cont / 2) - (obj / 2))

// Static Defines
Splash* Splash::_lpSplash = NULL;
HINSTANCE Splash::_hinstMainInst = NULL;

static Gdiplus::ImageAttributes iaAttr;
static Gdiplus::ColorMatrix ClrMatrix = { 
	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 0.0f, 1.0f
};

static Gdiplus::ColorMatrix ClrMatrixGlow = { 
	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
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

void Splash::rTweenCB_Hide(Tween* lpTween, R_TWEEN_CB_MSG code)
{
	// Get splash screen handle
	Splash* s = Get();

	// Get TweenEngine instance
	TweenEngine* te = TweenEngine::Get();

	// Switch callback type
	switch(code)
	{
	case PROGRESS:
		// Switch stage
		switch(lpTween->uArg.iInt)
		{
		case SPLASHANIM_FADE:
			// Set alpha of main logo
			s->_pngMainLogo->fAlpha = 1.0f - (float)lpTween->dEasedValue;

			break;
		case SPLASHANIM_SPLIT:
			// Set main logo X
			s->_pngMainLogo->frcDest->X = CENTERF(s->_pngMainLogo->frcDest->Width, s->_oGrphInf.szSize.cx) -
				((1.0f - (float)lpTween->dEasedValue) * CENTERF(s->_pngMainLogo->frcDest->Width, s->_oGrphInf.szSize.cx));

			// Set con bar src X
			s->_pngConBar->frcDest->X = s->_pngMainLogo->frcDest->X + 236;
			s->_pngConBar->frcSrc->X = s->_pngConBar->frcSrc->Width - (s->_pngConBar->frcSrc->Width * (1.0f - (float)lpTween->dEasedValue));
			break;
		case SPLASHANIM_TITLEFADE:
			// Set alpha
			s->_otpTitle.cAlpha = (unsigned char)((1.0f - (float)lpTween->dEasedValue) * 255);
			break;
		case SPLASHANIM_STUDFADE:
			// Set alpha
			s->_otpStudio.cAlpha = (unsigned char)((1.0f - (float)lpTween->dEasedValue) * 255);
			break;
		case SPLASHANIM_VERNAMEFADE:
			// Set alpha
			s->_otpVerName.cAlpha = (unsigned char)((1.0f - (float)lpTween->dEasedValue) * 255);
			break;
		case SPLASHANIM_VERFADE:
			// Set alpha
			s->_otpVer.cAlpha = (unsigned char)((1.0f - (float)lpTween->dEasedValue) * 255);
			break;
		case SPLASHANIM_CONFADE:
			// Set alpha
			s->_otpText.cAlpha = (unsigned char)((1.0f - (float)lpTween->dEasedValue) * 255);
			break;
		case SPLASHANIM_NATFADE:
			// Set alpha
			s->_pngNtgaLogo->fAlpha = (1.0f - (float)lpTween->dEasedValue);
			break;
		}

		// Break
		break;
	case FINISH:
		// Switch state
		switch(lpTween->uArg.iInt)
		{
		case SPLASHANIM_SPLIT:
			// Set conbar alpha to 0.0
			s->_pngConBar->fAlpha = 0.0f;
			break;
		case SPLASHANIM_FADE:
			// Hide window
			ShowWindowAsync(s->_hwndWindow, SW_HIDE);

			// Update the window
			UpdateWindow(s->_hwndWindow);

			// Set state
			s->_ssState = SPLASH_HIDDEN;

			break;
		}
	}
}

void Splash::Hide()
{
	// Check state
	if(_ssState != SPLASH_VISIBLE) return;

	// Log
	LOGD("Hiding splash screen");

	// Set state
	_ssState = SPLASH_HIDING;

	// Setup Tween information
	Tween* tNatFade = new Tween(300, 0, &rTweenCB_Hide, LINEAR);
	tNatFade->uArg.iInt = SPLASHANIM_NATFADE;

	Tween* tConFade = new Tween(300, 200, &rTweenCB_Hide, LINEAR);
	tConFade->uArg.iInt = SPLASHANIM_CONFADE;

	Tween* tVerFade = new Tween(300, 300, &rTweenCB_Hide, LINEAR);
	tVerFade->uArg.iInt = SPLASHANIM_VERFADE;

	Tween* tVerNameFade = new Tween(300, 600, &rTweenCB_Hide, LINEAR);
	tVerNameFade->uArg.iInt = SPLASHANIM_VERNAMEFADE;

	Tween* tStudioFade = new Tween(300, 800, &rTweenCB_Hide, LINEAR);
	tStudioFade->uArg.iInt = SPLASHANIM_STUDFADE;

	Tween* tTitleFade = new Tween(300, 1000, &rTweenCB_Hide, LINEAR);
	tTitleFade->uArg.iInt = SPLASHANIM_TITLEFADE;

	Tween* tSplit = new Tween(600, 1300, &rTweenCB_Hide, INOUT);
	tSplit->uArg.iInt = SPLASHANIM_SPLIT;

	Tween* tMainFade = new Tween(300, 1900, &rTweenCB_Hide, LINEAR);
	tMainFade->uArg.iInt = SPLASHANIM_FADE;

	// Send them on their way
	TweenEngine::Get()->Add(tMainFade);
	TweenEngine::Get()->Add(tSplit);
	TweenEngine::Get()->Add(tTitleFade);
	TweenEngine::Get()->Add(tStudioFade);
	TweenEngine::Get()->Add(tVerNameFade);
	TweenEngine::Get()->Add(tVerFade);
	TweenEngine::Get()->Add(tConFade);
	TweenEngine::Get()->Add(tNatFade);
}

void Splash::Show()
{
	// Check state
	if(_ssState != SPLASH_HIDDEN) return;

	// Log
	LOGD("Showing splash screen");

	// Set state
	_ssState = SPLASH_SHOWING;

	// Show the window
	ShowWindowAsync(_hwndWindow, SW_SHOWNORMAL);

	// Update the window
	UpdateWindow(_hwndWindow);

	// Set up initial positions/sizes
	_pngMainLogo->frcDest->X = CENTERF(_pngMainLogo->frcDest->Width, _oGrphInf.szSize.cx);
	
	_pngConBar->frcDest->X = CENTERF(_pngConBar->frcDest->Width, _oGrphInf.szSize.cx) + 110;
	_pngConBar->frcDest->Y = 119;
	_pngConBar->frcSrc->X = _pngConBar->frcSrc->Width;

	// Setup Tween information
	Tween* tMainFade = new Tween(300, 0, &rTweenCB_Show, LINEAR);
	tMainFade->uArg.iInt = SPLASHANIM_FADE;

	Tween* tCooloff = new Tween(800, 300, &rTweenCB_Show, EIN);
	tCooloff->uArg.iInt = SPLASHANIM_COOLOFF;

	Tween* tSplit = new Tween(700, 500, &rTweenCB_Show, INOUT);
	tSplit->uArg.iInt = SPLASHANIM_SPLIT;

	Tween* tTitleFade = new Tween(500, 1250, &rTweenCB_Show, LINEAR);
	tTitleFade->uArg.iInt = SPLASHANIM_TITLEFADE;

	Tween* tStudioFade = new Tween(500, 1350, &rTweenCB_Show, LINEAR);
	tStudioFade->uArg.iInt = SPLASHANIM_STUDFADE;

	Tween* tVerNameFade = new Tween(500, 1450, &rTweenCB_Show, LINEAR);
	tVerNameFade->uArg.iInt = SPLASHANIM_VERNAMEFADE;

	Tween* tVerFade = new Tween(500, 1550, &rTweenCB_Show, LINEAR);
	tVerFade->uArg.iInt = SPLASHANIM_VERFADE;

	Tween* tConFade = new Tween(500, 1650, &rTweenCB_Show, LINEAR);
	tConFade->uArg.iInt = SPLASHANIM_CONFADE;

	Tween* tNatFade = new Tween(600, 1800, &rTweenCB_Show, LINEAR);
	tNatFade->uArg.iInt = SPLASHANIM_NATFADE;

	// Send them on their way
	TweenEngine::Get()->Add(tMainFade);
	TweenEngine::Get()->Add(tCooloff);
	TweenEngine::Get()->Add(tSplit);
	TweenEngine::Get()->Add(tTitleFade);
	TweenEngine::Get()->Add(tStudioFade);
	TweenEngine::Get()->Add(tVerNameFade);
	TweenEngine::Get()->Add(tVerFade);
	TweenEngine::Get()->Add(tConFade);
	TweenEngine::Get()->Add(tNatFade);
}

void Splash::rTweenCB_Show(Tween* lpTween, R_TWEEN_CB_MSG code)
{
	// Get splash screen handle
	Splash* s = Get();

	// Get TweenEngine instance
	TweenEngine* te = TweenEngine::Get();

	// Init our warming/cooling tweens
	Tween* tWarm;
	Tween* tCool;

	// Switch callback type
	switch(code)
	{
	case PROGRESS:
		// Switch stage
		switch(lpTween->uArg.iInt)
		{
		case SPLASHANIM_FADE:
			// Set alpha of main logo
			s->_pngMainLogo->fAlpha = (float)lpTween->dEasedValue;

			// 'Heat Up' values
			//		Red
			ClrMatrixGlow.m[0][1] = (float)lpTween->dEasedValue;
			ClrMatrixGlow.m[0][2] = (float)lpTween->dEasedValue;
			//		Green
			ClrMatrixGlow.m[1][0] = (float)lpTween->dEasedValue;
			ClrMatrixGlow.m[1][2] = (float)lpTween->dEasedValue;
			//		Blue
			ClrMatrixGlow.m[2][0] = (float)lpTween->dEasedValue;
			ClrMatrixGlow.m[2][1] = (float)lpTween->dEasedValue;

			break;
		case SPLASHANIM_COOLOFF:
			// 'Heat Up' values
			//		Red
			ClrMatrixGlow.m[0][1] = 1.0f - (float)lpTween->dEasedValue;
			ClrMatrixGlow.m[0][2] = 1.0f - (float)lpTween->dEasedValue;
			//		Green
			ClrMatrixGlow.m[1][0] = 1.0f - (float)lpTween->dEasedValue;
			ClrMatrixGlow.m[1][2] = 1.0f - (float)lpTween->dEasedValue;
			//		Blue
			ClrMatrixGlow.m[2][0] = 1.0f - (float)lpTween->dEasedValue;
			ClrMatrixGlow.m[2][1] = 1.0f - (float)lpTween->dEasedValue;
			break;
		case SPLASHANIM_SPLIT:
			// Set main logo X
			s->_pngMainLogo->frcDest->X = CENTERF(s->_pngMainLogo->frcDest->Width, s->_oGrphInf.szSize.cx) -
				((FLOAT)lpTween->dEasedValue * CENTERF(s->_pngMainLogo->frcDest->Width, s->_oGrphInf.szSize.cx));

			// Set con bar src X
			s->_pngConBar->frcDest->X = s->_pngMainLogo->frcDest->X + 236;
			s->_pngConBar->frcSrc->X = s->_pngConBar->frcSrc->Width - (s->_pngConBar->frcSrc->Width * (float)lpTween->dEasedValue);
			break;
		case SPLASHANIM_TITLEFADE:
			// Set alpha
			s->_otpTitle.cAlpha = (unsigned char)(lpTween->dEasedValue * 255);
			break;
		case SPLASHANIM_STUDFADE:
			// Set alpha
			s->_otpStudio.cAlpha = (unsigned char)(lpTween->dEasedValue * 255);
			break;
		case SPLASHANIM_VERNAMEFADE:
			// Set alpha
			s->_otpVerName.cAlpha = (unsigned char)(lpTween->dEasedValue * 255);
			break;
		case SPLASHANIM_VERFADE:
			// Set alpha
			s->_otpVer.cAlpha = (unsigned char)(lpTween->dEasedValue * 255);
			break;
		case SPLASHANIM_CONFADE:
			// Set alpha
			s->_otpText.cAlpha = (unsigned char)(lpTween->dEasedValue * 255);
			break;
		case SPLASHANIM_NATFADE:
			// Set alpha
			s->_pngNtgaLogo->fAlpha = (float)(lpTween->dEasedValue);
			break;
		case SPLASHANIM_L_GLOW:
			// Warm it!
			// Green (Crazy how this light stuff works?)
			ClrMatrixGlow.m[1][0] = 0.65f * (float)(lpTween->dEasedValue);
			break;
		case SPLASHANIM_L_GFADE:
			// Cool it!
			// Green (Crazy how this light stuff works?)
			ClrMatrixGlow.m[1][0] = 0.65f * (1.0f - (float)(lpTween->dEasedValue));
			break;
		}

		// Break
		break;
	case FINISH:
		// Switch state
		switch(lpTween->uArg.iInt)
		{
		case SPLASHANIM_L_GFADE:
			// Check if we're fading
			if(s->_ssState == SPLASH_HIDING || s->_ssState == SPLASH_HIDDEN)
				break;
		case SPLASHANIM_COOLOFF:
			// Start glow
			tWarm = new Tween(1500, 100, &rTweenCB_Show, EIN);
			tWarm->uArg.iInt = SPLASHANIM_L_GLOW;
			te->Add(tWarm);

			tCool = new Tween(1700, 1600, &rTweenCB_Show, EOUT);
			tCool->uArg.iInt = SPLASHANIM_L_GFADE;
			te->Add(tCool);
			break;
		case SPLASHANIM_FADE:
			// Set conbar alpha to 1.0
			s->_pngConBar->fAlpha = 1.0f;
			break;
		case SPLASHANIM_NATFADE:
			// Set state
			s->_ssState = SPLASH_VISIBLE;
			break;
		}
	}
}

void Splash::ShowWait()
{
	// Call Show
	Show();

	// Wait
	while(_ssState != SPLASH_VISIBLE)
		Sleep(1);
}

void Splash::HideWait()
{
	// Call Hide
	Hide();

	// Wait
	while(_ssState != SPLASH_HIDDEN)
		Sleep(1);
}

/**
 * NOTE: ALWAYS USE A STRING FORMATTED WITH FORMATSTRINGW!!!!
 *	This frees the local buffer, which doesn't exist if a static string
 *	is used!
 */
void Splash::UpdateStatus(const wchar_t* szString)
{
	// Free buffer if not NULL
	if(_wcsStatus != NULL)
		LocalFree(_wcsStatus);

	// Set buffer
	_wcsStatus = const_cast<wchar_t*>(szString);
}

Splash::Splash()
{
	// Set initial states
	_ssState = SPLASH_HIDDEN;
	_ssAnimState = SPLASHANIM_FADE;
	_wcsStatus = const_cast<wchar_t*>(SGETSTRING(R_SPLASH_MSG_LOADING));

	// Load Fonts
	if(AddFontResourceExW(StringMgr::Get()->GetString(R_SPLASH_TITLE_FONT_FILENAME), FR_PRIVATE, 0) == 0)
	{
		// Log and break
		LOGW("Could not load rezland font!");
		assert(false);
	}

	// Load PNGs
	_pngMainLogo = new PNG(R_PNG_SPLASH_MAIN_LOGO);
	_pngConBar = new PNG(R_PNG_SPLASH_CONBAR);
	_pngNtgaLogo = new PNG(R_PNG_SPLASH_NTGA_LOGO);

	// Set logo pos
	_pngNtgaLogo->frcDest->X = 770;
	_pngNtgaLogo->frcDest->Y = 350;

	// Set up font information
	_otpTitle.ffFontFam = new FontFamily(StringMgr::Get()->GetString(R_SPLASH_TITLE_FONT), NULL);
	_otpTitle.fntFont = new Font(_otpTitle.ffFontFam, 72.0f, FontStyleRegular, UnitPixel);
	_otpTitle.brshBrush = new SolidBrush(Color(255, 231, 162, 0));
	_otpTitle.cAlpha = 0;
	_otpTitle.sfFormat = new StringFormat(0, LANG_NEUTRAL);
	_otpTitle.sfFormat->SetLineAlignment(StringAlignmentFar);

	_otpStudio.ffFontFam = new FontFamily(StringMgr::Get()->GetString(R_SPLASH_AUX_FONT), NULL);
	_otpStudio.fntFont = new Font(_otpStudio.ffFontFam, 14.0f, FontStyleRegular, UnitPixel);
	_otpStudio.brshBrush = new SolidBrush(Color(255, 170, 119, 0));
	_otpStudio.cAlpha = 0;
	_otpStudio.sfFormat = new StringFormat(0, LANG_NEUTRAL);
	_otpStudio.sfFormat->SetLineAlignment(StringAlignmentFar);

	_otpVerName.ffFontFam = new FontFamily(StringMgr::Get()->GetString(R_SPLASH_AUX_FONT), NULL);
	_otpVerName.fntFont = new Font(_otpVerName.ffFontFam, 18.0f, FontStyleRegular, UnitPixel);
	_otpVerName.brshBrush = new SolidBrush(Color(255, 110, 110, 110));
	_otpVerName.cAlpha = 0;
	_otpVerName.sfFormat = new StringFormat(0, LANG_NEUTRAL);
	_otpVerName.sfFormat->SetAlignment(StringAlignmentFar);
	_otpVerName.sfFormat->SetLineAlignment(StringAlignmentFar);

	_otpVer.ffFontFam = new FontFamily(StringMgr::Get()->GetString(R_SPLASH_AUX_FONT), NULL);
	_otpVer.fntFont = new Font(_otpVer.ffFontFam, 9.0f, FontStyleRegular, UnitPixel);
	_otpVer.brshBrush = new SolidBrush(Color(255, 110, 110, 110));
	_otpVer.cAlpha = 0;
	_otpVer.sfFormat = new StringFormat(0, LANG_NEUTRAL);
	_otpVer.sfFormat->SetLineAlignment(StringAlignmentFar);
	
	_otpText.ffFontFam = new FontFamily(StringMgr::Get()->GetString(R_SPLASH_AUX_FONT), NULL);
	_otpText.fntFont = new Font(_otpText.ffFontFam, 11.0f, FontStyleRegular, UnitPixel);
	_otpText.brshBrush = new SolidBrush(Color(255, 151, 150, 150));
	_otpText.cAlpha = 0;
	_otpText.sfFormat = new StringFormat(0, LANG_NEUTRAL);
	

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
	_hwndWindow = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
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

	_oGrphInf.graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);
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
		s->DrawPNG(Get()->_pngConBar);
		s->DrawPNG(Get()->_pngMainLogo, &ClrMatrixGlow);
		s->DrawPNG(Get()->_pngNtgaLogo);

		// Draw Text
		s->_oGrphInf.graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);
		s->DrawString(SGETSTRING(R_TITLE), 430, 211, &s->_otpTitle);
		s->DrawString(SGETSTRING(R_SPLASH_STUDIO), 554, 190, &s->_otpStudio);
		s->DrawString(SGETSTRING(VER), 845, 192, &s->_otpVerName);

		s->_oGrphInf.graphics->SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
		s->DrawString(SGETSTRING(VER_N), 843, 188, &s->_otpVer);
		s->DrawString(SGETSTRING(R_LICENSE, L"Qix"), 434, 210, &s->_otpText);
		s->DrawString(s->_wcsStatus, 434, 250, &s->_otpText, false);
		s->DrawString(SGETSTRING(R_COPYRIGHT), 434, 320, &s->_otpText);

		// Call UpdateLayeredWindow
		UpdateLayeredWindow(s->_hwndWindow, s->_oGrphInf.hdcScreen, NULL, &s->_oGrphInf.szSize, s->_oGrphInf.hdcMem, &s->_oGrphInf.ptSrcPos, 0, &s->_oGrphInf.blend, ULW_ALPHA);

		// Sleep!
		Sleep(1000 / R_SPLASH_DRAW_FPS);
	}

	// Return 
	return 0;
}

void Splash::DrawString(const wchar_t* str, float x, float y, RSPL_TEXT_PROPS* prop, bool bFree)
{
	// Check alpha
	if(prop->cAlpha == 0)
		return;

	// Get length
	int len = (int)wcslen(str);
	
	// Setup point
	PointF pos(x, y);

	// Set alpha
	Color col;
	prop->brshBrush->GetColor(&col);
	Color ncol(prop->cAlpha, col.GetR(), col.GetG(), col.GetB());
	prop->brshBrush->SetColor(ncol);

	// Draw
	_oGrphInf.graphics->DrawString(str, len, prop->fntFont, pos, prop->sfFormat, prop->brshBrush);

	// Flush
	_oGrphInf.graphics->Flush();

	// Release string if needed
	if(bFree)
		LocalFree((LPVOID)str);
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

void Splash::DrawPNG(PNG* lpPNG, ColorMatrix* cmMatrix)
{
	// Check alpha
	if(lpPNG->fAlpha <= 0.0f) return;

	// Check cmMatrix for null
	if(cmMatrix == NULL) cmMatrix = &ClrMatrix;

	// Set alpha
	cmMatrix->m[3][3] = lpPNG->fAlpha;
	Gdiplus::ImageAttributes iaAttr;
	iaAttr.SetColorMatrix(cmMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
	
	// Draw
	_oGrphInf.graphics->DrawImage(lpPNG->GetImage(), *lpPNG->frcDest, lpPNG->frcSrc->X, lpPNG->frcSrc->Y, lpPNG->frcSrc->Width, lpPNG->frcSrc->Height, Gdiplus::UnitPixel, &iaAttr);
	_oGrphInf.graphics->Flush();
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

	// Delete font information
	delete _otpTitle.brshBrush;
	delete _otpTitle.ffFontFam;
	delete _otpTitle.fntFont;
	delete _otpTitle.sfFormat;

	delete _otpStudio.brshBrush;
	delete _otpStudio.ffFontFam;
	delete _otpStudio.fntFont;
	delete _otpStudio.sfFormat;

	delete _otpText.brshBrush;
	delete _otpText.ffFontFam;
	delete _otpText.fntFont;
	delete _otpText.sfFormat;

	delete _otpVer.brshBrush;
	delete _otpVer.ffFontFam;
	delete _otpVer.fntFont;
	delete _otpVer.sfFormat;

	delete _otpVerName.brshBrush;
	delete _otpVerName.ffFontFam;
	delete _otpVerName.fntFont;
	delete _otpVerName.sfFormat;

	// Free status buffer
	LocalFree(_wcsStatus);

	// Delete PNG objects
	delete _pngMainLogo;
	delete _pngConBar;
	delete _pngNtgaLogo;

	// Set pointer to NULL
	Splash::_lpSplash = NULL;
}