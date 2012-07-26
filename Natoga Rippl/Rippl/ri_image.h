/************************************************************************/
/* SDL_Image Wrapper                                                    */
/************************************************************************/
#ifndef ri_image_h__
#define ri_image_h__

// Includes
#include "SDL_image.h"

// Sprite Orientation Settings
typedef enum
{
	VERTICLE,
	HORIZONTAL
} R_SPRITE_DIRECTION;

// SDL Image Wrapper Class
class RIImage
{
public:
	RIImage(const char* szPathTo);
	~RIImage();

	SDL_Surface*			ImageSurface;
	SDL_Rect				Bounds;

	void					SetSpriteSize(int iSize, R_SPRITE_DIRECTION eDirection);
	SDL_Rect				GetSprite(unsigned short sIndex);
protected:
	int						_iSpriteSize;
	R_SPRITE_DIRECTION		_eDirection;
};

#endif // ri_image_h__