/************************************************************************/
/* Splash Screen Interface                                              */
/************************************************************************/
#ifndef iSplashScreen_h__
#define iSplashScreen_h__

// Interface Definition
interface iSplashScreen
{
public:
	virtual void Show() = 0;
	virtual void ShowWait() = 0;
	virtual void Hide() = 0;
	virtual void HideWait() = 0;
	virtual void UpdateStatus(const wchar_t* szString) = 0;
};

#endif // iSplashScreen_h__