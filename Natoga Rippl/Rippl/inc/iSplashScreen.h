/************************************************************************/
/* Splash Screen Interface                                              */
/************************************************************************/

// Interface Definition
interface iSplashScreen
{
	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual void UpdateStatus(const char* szString) = 0;
};