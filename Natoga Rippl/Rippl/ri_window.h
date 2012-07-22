/************************************************************************/
/* Rippl Interface Main Window                                          */
/************************************************************************/
#ifndef ri_window_h__
#define ri_window_h__

// Main Window Class Definition
class RIWindow
{
public:
	/**
	 * Initializes the main window
	 */
	static void					Init(HINSTANCE hinst);

	/**
	 * Destroys the main window
	 */
	static void					Destroy();

	/**
	 * Hides the window
	 */
	void						Hide();

	/**
	 * Shows the window
	 */
	void						Show();

	static RIWindow*			Inst;
private:
	static LRESULT				WinMsgHandler(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	RIWindow(HINSTANCE hinst);
	~RIWindow();

	void						SetupClass();
	void						RegClass();

	void						MakeWindow();
	void						KillWindow();
	
	WNDCLASSEX					_wcxClass;
	HINSTANCE					_hInst;
	ATOM						_aAtom;
	HWND						_hwndWindow;
};



#endif // ri_window_h__