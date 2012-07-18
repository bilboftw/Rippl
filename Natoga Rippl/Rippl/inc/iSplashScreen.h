/************************************************************************/
/* Splash Screen Interface                                              */
/************************************************************************/
#ifndef iSplashScreen_h__
#define iSplashScreen_h__

// Interface Definition
interface iSplashScreen
{
	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual void UpdateStatus(const char* szString) = 0;
};

#endif // iSplashScreen_h__