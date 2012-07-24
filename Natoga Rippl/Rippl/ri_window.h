/************************************************************************/
/* Rippl Interface Main Window                                          */
/************************************************************************/
#ifndef ri_window_h__
#define ri_window_h__

// Includes
#include "SDL.h"

#include "ri_container.h"

// Main Window Class Definition
class RIWindow : public RIContainer
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

	void						Update(RIContainer* ricChild);
	void						OnDraw();

	static RIWindow*			Inst;

	SDL_Renderer*				Renderer;

	SDL_Window*					Window;

	SDL_PixelFormat				GlobalPixelFormat;
			
private:
	RIWindow();
	~RIWindow();

	void						MakeWindow();
	void						KillWindow();

	void						GetRenderer();
	void						ClearWindow();

	void						DrawBackground();

	void						SetupGlobalPixelFormat();

	SDL_Surface*				_imgBG;
};



#endif // ri_window_h__