/************************************************************************/
/* Rippl Interface Main Window                                          */
/************************************************************************/

// Includes
#include "resource.h"
#include "Macros.h"
#include "SDL_image.h"
#include "r_str.h"

#include "r_themes.h"
#include "ri_window.h"

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
	// Set BG img to NULL
	_imgBG = NULL;

	// Create window
	MakeWindow();

	// Set up global pixel format
	SetupGlobalPixelFormat();

	// Show window
	Show();

	// Get the renderer
	GetRenderer();

	// Init window
	ClearWindow();
}

RIWindow::~RIWindow()
{
	// Release renderer
	SDL_DestroyRenderer(Renderer);

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

void RIWindow::GetRenderer()
{
	// Create Renderer and check
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if(Renderer == NULL)
	{
		// Warn and break
		LOGE("Could not create RI window renderer: %s", SDL_GetError());
		assert(false);
	}
}

void RIWindow::ClearWindow()
{
	// Set color to grey
	SDL_SetRenderDrawColor(Renderer, 0x22, 0x22, 0x22, 255);

	// Fill the renderer
	SDL_RenderClear(Renderer);	

	// Update window
	SDL_RenderPresent(Renderer);
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

void RIWindow::OnDraw()
{
	// Clear window
	ClearWindow();

	// Draw background
	DrawBackground();
}

void RIWindow::Update(RIContainer* ricChild)
{
	// Update
	SDL_UpdateWindowSurfaceRects(Window, ricChild->GetBounds(), 1);
}

void RIWindow::DrawBackground()
{
	// Get window surface
	SDL_Surface* winSurf = SDL_GetWindowSurface(Window);

	// Get window size
	int w;
	int h;
	SDL_GetWindowSize(Window, &w, &h);

	// Set up rects
	SDL_Rect srBnds;
	
	// Loop
	for(srBnds.x = 0; srBnds.x < w; srBnds.x += RTheme::Loaded->Theme.UI.MainWindow.Background->Bounds.w)
		for(srBnds.y = 0; srBnds.y < h; srBnds.y += RTheme::Loaded->Theme.UI.MainWindow.Background->Bounds.h)
		{
			// Setup sizes
			srBnds.w = RTheme::Loaded->Theme.UI.MainWindow.Background->Bounds.w;
			srBnds.h = RTheme::Loaded->Theme.UI.MainWindow.Background->Bounds.h;

			// Blit
			if(SDL_BlitSurface(RTheme::Loaded->Theme.UI.MainWindow.Background->ImageSurface,
							&RTheme::Loaded->Theme.UI.MainWindow.Background->CloneBounds(),
							winSurf,
							&srBnds) != 0)
				LOGW("Could not blit: %s", SDL_GetError());
		};

	// Update
	if(SDL_UpdateWindowSurface(Window) != 0)
		LOGW("Could not update surface: %s", SDL_GetError());
}