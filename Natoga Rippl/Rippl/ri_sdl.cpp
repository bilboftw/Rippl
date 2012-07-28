/************************************************************************/
/* SDL Main Functions                                                   */
/************************************************************************/

// Includes
#include "SDL.h"
#include "Macros.h"
#include "SDL_image.h"

#include "ri_sdl.h"

void RSDL::Init()
{
	// Initialize
	LOGI("Init'ing SDL (watch out!...)");

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		LOGE("Could not start SDL: %s", SDL_GetError());

	// Init Images
	if(IMG_Init(IMG_INIT_PNG) == 0)
		// Error and break
		LOGE("Could not init images: %s", IMG_GetError());
}

void RSDL::Shutdown()
{
	// Shutdown Images
	IMG_Quit();

	// Shutdown
	LOGI("Shutting down SDL...");
	SDL_Quit();
}