/************************************************************************/
/* Rippl Interface Main Window                                          */
/************************************************************************/
#ifndef ri_window_h__
#define ri_window_h__

// Includes
#include "SDL.h"

// Main Window Class Definition
class RIWindow
{
public:
	/**
	 * Initializes the main window
	 */
	static void					Init();

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

	SDL_Surface*				Surface;

	SDL_Window*					Window;

	SDL_PixelFormat				GlobalPixelFormat;
			
private:
	RIWindow();
	~RIWindow();

	void						MakeWindow();
	void						KillWindow();

	void						GetSurface();
	void						InitWindow();

	void						SetupGlobalPixelFormat();
};



#endif // ri_window_h__