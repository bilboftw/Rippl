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

	// Create helper bounds rect
	Bounds.x = 0;
	Bounds.y = 0;
	Bounds.w = ImageSurface->w;
	Bounds.h = ImageSurface->h;

	// Set sprite size to 0 and default direction
	_iSpriteSize = 0;
	_eDirection = VERTICLE;
}

void RIImage::SetSpriteSize(int iSize, R_SPRITE_DIRECTION eDirection)
{
	// Set sizes
	_iSpriteSize = iSize;
	_eDirection = eDirection;
}

SDL_Rect RIImage::GetSprite(unsigned short sIndex)
{
	// Re-create bounds
	SDL_Rect ret = Bounds;

	// Check direction
	switch(_eDirection)
	{
	case VERTICLE:
		// Set height
		ret.h = _iSpriteSize;

		// Calculate offset
		ret.y += _iSpriteSize * sIndex;
		break;
	case HORIZONTAL:
		// Set width
		ret.w = _iSpriteSize;

		// Calculate offset
		ret.x += _iSpriteSize * sIndex;
		break;
	}

	// Return
	return ret;
}

RIImage::~RIImage()
{
	// Free
	SDL_FreeSurface(ImageSurface);
}