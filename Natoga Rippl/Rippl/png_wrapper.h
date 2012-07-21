/************************************************************************/
/* PNG Resource Wrapper                                                 */
/************************************************************************/
#ifndef png_wrapper_h__
#define png_wrapper_h__

// Include the lib
#pragma comment(lib, "Gdiplus.lib")

// Includes
#include <windows.h>
#include <GdiPlus.h>
#include <GdiPlusHeaders.h>

// Using Gdiplus
using namespace Gdiplus;

// PNG Class
class PNG
{
public:
	PNG(UINT iRes);
	~PNG();
	Gdiplus::Image*			GetImage() { return _imgImage; };

	RectF*					frcSrc;
	RectF*					frcDest;
	float					fAlpha;
protected:
	IStream*				GetIStream();
	UINT					_iRes;
	IStream*				_lpIStream;
	Gdiplus::Image*			_imgImage;
};

#endif // png_wrapper_h__