/************************************************************************/
/* SDL Main Functions                                                   */
/************************************************************************/

// Includes
#include "SDL.h"
#include "Macros.h"

#include "ri_sdl.h"

void RSDL::Init()
{
	// Initialize
	LOGI("Init'ing SDL (watch out!...)");

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		LOGE("Could not start SDL: %s", SDL_GetError());
}

void RSDL::Shutdown()
{
	// Shutdown
	LOGI("Shutting down SDL...");
	SDL_Quit();
}