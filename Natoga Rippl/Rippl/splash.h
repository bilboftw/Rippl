/************************************************************************/
/* Splash Screen Implementation                                         */
/************************************************************************/
#ifndef splash_h__
#define splash_h__

// Includes
#include <windows.h>

#include "iSplashScreen.h"

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
	void							Hide();
	void							UpdateStatus(const char* szString);

protected:
	static Splash*					_lpSplash;
	static HINSTANCE				_hinstMainInst;

	bool							_bAnimating;
	R_SPLASH_STATE					_ssState;
	R_SPLASH_ANIM_STATE				_ssAnimState;

	HWND							_hwndWindow;
private:
	Splash() {};
	~Splash();
};

#endif // splash_h__