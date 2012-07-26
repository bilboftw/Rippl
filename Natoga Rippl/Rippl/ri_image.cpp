/************************************************************************/
/* SDL_Image Wrapper                                                    */
/************************************************************************/

// Includes
#include "SDL.h"
#include "SDL_image.h"
#include "Macros.h"

#include "ri_image.h"

RIImage::RIImage(const char* szPathTo)
{
	// Load image
	ImageSurface = IMG_Load(szPathTo);
	if(ImageSurface == NULL)
	{
		LOGW("Could not load PNG File: %s", IMG_GetError());
		assert(false);
		return;
	}
}

RIImage::~RIImage()
{
	// Free
	SDL_FreeSurface(ImageSurface);
}