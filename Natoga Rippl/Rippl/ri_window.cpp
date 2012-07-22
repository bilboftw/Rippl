/************************************************************************/
/* Rippl Interface Main Window                                          */
/************************************************************************/

// Includes
#include <windows.h>

#include "resource.h"
#include "Macros.h"

#include "ri_window.h"
#include "strmgr.h"

// Static Defines
RIWindow* RIWindow::Inst = NULL;

void RIWindow::Init()
{
	// Create new instance
	Inst = new RIWindow();
}

void RIWindow::Destroy()
{
	// Delete object
	delete Inst;

	// Set to NULL
	Inst = NULL;
}

RIWindow::RIWindow()
{
	// Create window
	MakeWindow();

	// Set up global pixel format
	SetupGlobalPixelFormat();

	// Get the surface
	GetSurface();

	// Init window
	InitWindow();

	// Show window
	Show();
}

RIWindow::~RIWindow()
{
	// Destroy Window
	KillWindow();
}

void RIWindow::MakeWindow()
{
	// Create window
	Window = SDL_CreateWindow(	"Rippl Studio",
								SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								1024, 768,
								SDL_WINDOW_SHOWN |
									SDL_WINDOW_BORDERLESS |
									SDL_WINDOW_INPUT_FOCUS
								);

	// Check
	if(Window == NULL)
		// Log
		LOGE("Could not create main RI window: %s", SDL_GetError());
}

void RIWindow::KillWindow()
{
	// Destroy window
	SDL_DestroyWindow(Window);
}

void RIWindow::Show()
{
	// Show window
	SDL_ShowWindow(Window);
}

void RIWindow::Hide()
{
	// Hide window
	SDL_HideWindow(Window);
}

void RIWindow::GetSurface()
{
	// Get the window's surface
	Surface = SDL_GetWindowSurface(Window);

	// Check
	if(Surface == NULL)
		// Log
		LOGE("Could not get surface of RI window: %s", SDL_GetError());
}

void RIWindow::InitWindow()
{
	// Fill the window with black
	//SDL_MapRGBA(&GlobalPixelFormat, 0, 0, 0, 255)
	if(SDL_FillRect(Surface, NULL, 0xFF000000) < 0)
		// Log
		LOGE("Could not fill surface with base black: %s", SDL_GetError());

	// Update window surface
	SDL_UpdateWindowSurface(Window);
}

void RIWindow::SetupGlobalPixelFormat()
{
	// Set up the global pixel format struct
	memset(&GlobalPixelFormat, 0, sizeof(GlobalPixelFormat));
	GlobalPixelFormat.format = SDL_PIXELFORMAT_ARGB8888;
	GlobalPixelFormat.palette = NULL;
	GlobalPixelFormat.BitsPerPixel = 8;
	GlobalPixelFormat.BytesPerPixel = 1;
	GlobalPixelFormat.Amask = 0xFF000000;
	GlobalPixelFormat.Rmask = 0x00FF0000;
	GlobalPixelFormat.Gmask = 0x0000FF00;
	GlobalPixelFormat.Bmask = 0x000000FF;
}