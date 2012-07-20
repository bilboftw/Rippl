/************************************************************************/
/* PNG Resource Wrapper                                                 */
/************************************************************************/
#ifndef png_wrapper_h__
#define png_wrapper_h__

// Include the lib
#pragma comment(lib, "windowscodecs.lib")

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
	SIZE					GetSize() { return _szSize; };
	BITMAPINFO*				GetBMPInfo() { return &_bmiInfo; };
protected:
	UINT					_iRes;
	IStream*				_lpIStream;
	HBITMAP					_hbmpHandle;
	IWICBitmapSource*		_iwicBMPRes;
	SIZE					_szSize;
	BITMAPINFO				_bmiInfo;
};

#endif // png_wrapper_h__