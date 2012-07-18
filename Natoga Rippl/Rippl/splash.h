/************************************************************************/
/* Splash Screen Implementation                                         */
/************************************************************************/
#ifndef splash_h__
#define splash_h__

// Includes
#include <windows.h>

#include "iSplashScreen.h"

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
	SPLASHANIM_VERFADE,		// The version name/number fades in
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
	void							UpdateStatus(const char* szString);

protected:
	static Splash*					_lpSplash;
	static HINSTANCE				_hinstMainInst;
	static LRESULT CALLBACK			SplashProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

	R_SPLASH_STATE					_ssState;
	R_SPLASH_ANIM_STATE				_ssAnimState;

	HWND							_hwndWindow;
	WNDCLASSEX						_wcWClass;
	ATOM							_atomWinAtom;
	RECT							_rcSize;

	Tween*							_twnFade;
private:
	void							SetupShowTweenInfo();
	
	void							rTweenCB(Tween* lpTween, R_TWEEN_CB_MSG code);

	Splash();
	~Splash();
};

#endif // splash_h__