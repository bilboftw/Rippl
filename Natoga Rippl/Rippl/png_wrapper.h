/************************************************************************/
/* PNG Resource Wrapper                                                 */
/************************************************************************/
#ifndef png_wrapper_h__
#define png_wrapper_h__

// Includes
#include <windows.h>
#include <wincodec.h>

// PNG Class
class PNG
{
public:
	PNG(UINT iRes);
	~PNG();
	IStream*				GetIStream();
	HBITMAP					GetBitmap();
	IWICBitmapSource*		GetIWICSource();
protected:
	UINT					_iRes;
	IStream*				_lpIStream;
	HBITMAP					_hbmpHandle;
	IWICBitmapSource*		_iwicBMPRes;
	
};

#endif // png_wrapper_h__