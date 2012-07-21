/************************************************************************/
/* Splash Screen Implementation                                         */
/************************************************************************/
#ifndef splash_h__
#define splash_h__

// Define FPS
#define R_SPLASH_DRAW_FPS 100

// Includes
#include <windows.h>

#include "iSplashScreen.h"

#include "png_wrapper.h"
#include "tween_engine.h"

// Splash State Enum
typedef enum
{
	SPLASH_HIDDEN,
	SPLASH_SHOWING,
	SPLASH_VISIBLE,
	SPLASH_HIDING
} R_SPLASH_STATE;

// Splash Animation Progression State Enum
typedef enum
{
	SPLASHANIM_FADE,		// The logo fades in
	SPLASHANIM_SPLIT,		// The logo slides left and reveals the 'console bar'
	SPLASHANIM_TITLEFADE,	// The rippl title fades in
	SPLASHANIM_STUDFADE,	// Studio text fade
	SPLASHANIM_VERNAMEFADE,	// The version name fades in
	SPLASHANIM_VERFADE,		// The version number fades in
	SPLASHANIM_CONFADE,		// The default console text fades in
	SPLASHANIM_NATFADE		// The Natoga logo fades in
} R_SPLASH_ANIM_STATE;

// Splash Class Implementation Declaration
class Splash : public iSplashScreen
{
public:
	static void						Init(HINSTANCE hinstInst);
	static Splash*					Get();
	static void						Destroy();
	
	void							Show();
	void							ShowWait();
	void							Hide();
	void							HideWait();
	void							UpdateStatus(const wchar_t* szString);

protected:
	static Splash*					_lpSplash;
	static HINSTANCE				_hinstMainInst;
	static LRESULT CALLBACK			SplashProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
	static DWORD					SplashGraphicsDrawEP(PVOID arg);

									struct RSPL_TEXT_PROPS
									{
										FontFamily* ffFontFam;
										Font* fntFont;
										SolidBrush* brshBrush;
										unsigned char cAlpha;
										StringFormat* sfFormat;
									} _otpTitle, _otpStudio, _otpVer, _otpVerName, _otpText;

	void							DrawPNG(PNG* lpPNG);
	void							DrawString(const wchar_t* str, float x, float y, RSPL_TEXT_PROPS* prop, bool bFree = true);

	HANDLE							hDrawThread;

	R_SPLASH_STATE					_ssState;
	R_SPLASH_ANIM_STATE				_ssAnimState;

	HWND							_hwndWindow;
	WNDCLASSEX						_wcWClass;
	ATOM							_atomWinAtom;
	RECT							_rcSize;

	PNG*							_pngMainLogo;
	PNG*							_pngConBar;

	wchar_t*						_wcsStatus;
									struct RSPL_GRAPHICS_INFO
									{
										SIZE							szSize;
										Gdiplus::Graphics*				graphics;
										HDC								hdcScreen;
										HDC								hdcMem;
										HBITMAP							hBmp;
										HBITMAP							hBmpOld;
										BLENDFUNCTION					blend;
										POINT							ptSrcPos;
									} _oGrphInf;
private:
	static void						rTweenCB(Tween* lpTween, R_TWEEN_CB_MSG code);

	Splash();
	~Splash();
};

#endif // splash_h__