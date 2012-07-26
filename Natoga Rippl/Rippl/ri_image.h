/************************************************************************/
/* SDL_Image Wrapper                                                    */
/************************************************************************/
#ifndef ri_image_h__
#define ri_image_h__

// Includes
#include "SDL_image.h"

// SDL Image Wrapper Class
class RIImage
{
public:
	RIImage(const char* szPathTo);
	~RIImage();

	SDL_Surface*			ImageSurface;
};

#endif // ri_image_h__