/************************************************************************/
/* PNG Resource Wrapper                                                 */
/************************************************************************/

// Includes
#include <windows.h>
#include <wincodec.h>

#include "Macros.h"

#include "png_wrapper.h"

PNG::PNG(UINT iRes)
{
	// Store
	_iRes = iRes;

	// Init pointers/handles
	_hbmpHandle = NULL;
	_iwicBMPRes = NULL;
	_lpIStream = NULL;
	_szSize.cx = 0;
	_szSize.cy = 0;
}

IStream* PNG::GetIStream()
{
	// Find resource and check
	HRSRC hrRes = FindResource(NULL, MAKEINTRESOURCE(_iRes), "PNG");
	if(hrRes == NULL)
	{
		// Warn, break, and return
		LOGE("Could not find resource %u: %u", _iRes, GetLastError());
		assert(false);
		return NULL;
	}

	// Load Resource and check
	DWORD dwResSize = SizeofResource(NULL, hrRes);
	HGLOBAL hgRes = LoadResource(NULL, hrRes);
	if(hgRes == NULL)
	{
		// Warn, break, and return
		LOGE("Could not load resource %u: %u", _iRes, GetLastError());
		assert(false);
		return NULL;
	}

	// Lock the resource and check
	LPVOID lpResData = LockResource(hgRes);
	if(lpResData == NULL)
	{
		// Warn break and return
		LOGE("Could not lock resource %u for image load: %u", _iRes, GetLastError());
		assert(false);
		return NULL;
	}

	// Allocate memory to hold resource data and, alas, check
	HGLOBAL hgData = GlobalAlloc(GMEM_MOVEABLE, dwResSize);
	if(hgData == NULL)
	{
		// Warn break return
		LOGE("Could not allocate global data for resource %u: %u", _iRes, GetLastError());
		assert(false);
		return NULL;
	}

	// Get pointer to allocated memory and check
	LPVOID lpData = GlobalLock(hgData);
	if(lpData == NULL)
	{
		// Warn break return
		LOGE("Could not lock allocated memory for resource %u: %u", _iRes, GetLastError());
		assert(false);
		return NULL;
	}

	// Copy data and unlock original data
	CopyMemory(lpData, lpResData, dwResSize);
	GlobalUnlock(hgRes);

	// Create iStream
	if(FAILED(CreateStreamOnHGlobal(hgData, TRUE, &_lpIStream)))
	{
		// Warn break and return
		LOGE("Could not create IStream handle for resource %u: %u", _iRes, GetLastError());
		assert(false);
		return NULL;
	}

	// Return
	return _lpIStream;
}

IWICBitmapSource* PNG::GetIWICSource()
{
	// Load decoder
	IWICBitmapDecoder* lpDecoder = NULL;
	if(FAILED(CoCreateInstance(CLSID_WICPngDecoder, NULL, CLSCTX_INPROC_SERVER, __uuidof(lpDecoder), reinterpret_cast<void**>(&lpDecoder))))
	{
		// Warn, break and return
		LOGE("Could not create decoder instance for resource %u!", _iRes);
		assert(false);
		return NULL;
	}

	// Load PNG
	if(FAILED(lpDecoder->Initialize(_lpIStream, WICDecodeMetadataCacheOnLoad)))
	{
		// Warn, break and return
		LOGE("Could not init decoder for resource %u!", _iRes);
		assert(false);
		return NULL;
	}

	// Check for first frame
	UINT iFrameCount = 0;
	if(FAILED(lpDecoder->GetFrameCount(&iFrameCount)) || iFrameCount == 0)
	{
		// Warn, break and return
		LOGE("Either the frame count could not be recv'd, or the frame count is 0 for resource %u", _iRes);
		assert(false);
		return NULL;
	}

	// Load the first frame 
	IWICBitmapFrameDecode* lpFrame = NULL;
	if(FAILED(lpDecoder->GetFrame(0, &lpFrame)))
	{
		// Warn, break, return
		LOGE("Could not load first frame for resource %u", _iRes);
		assert(false);
		return NULL;
	}

	// Convert image to 32BPP BGRA format
	WICConvertBitmapSource(GUID_WICPixelFormat32bppPBGRA, lpFrame, &_iwicBMPRes);
	
	// Release handles
	lpFrame->Release();
	lpDecoder->Release();

	// Return
	return _iwicBMPRes;
}

HBITMAP PNG::GetBitmap()
{
	// Check if we already have it
	if(_hbmpHandle != NULL)
		// Return
		return _hbmpHandle;

	// Create stream
	GetIStream();

	// Create WIC handle
	GetIWICSource();

	// Get size
	if(FAILED(_iwicBMPRes->GetSize((UINT*)&_szSize.cx, (UINT*)&_szSize.cy)) || _szSize.cx == 0 || _szSize.cy == 0)
	{
		// Warn break and return
		LOGE("Could not get image size, or image size is 0 for resource %u", _iRes);
		assert(false);
		return NULL;
	}

	// Create bitmap info object
	ZeroMemory(&_bmiInfo, sizeof(_bmiInfo));
	_bmiInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	_bmiInfo.bmiHeader.biWidth = _szSize.cx;
	_bmiInfo.bmiHeader.biHeight = -((LONG) _szSize.cy);
	_bmiInfo.bmiHeader.biPlanes = 1;
	_bmiInfo.bmiHeader.biBitCount = 32;
	_bmiInfo.bmiHeader.biCompression = BI_RGB;

	// Create DIB section
	void* lpImageBits = NULL;
	HDC hdcScreen = GetDC(NULL);
	_hbmpHandle = CreateDIBSection(hdcScreen, &_bmiInfo, DIB_RGB_COLORS, &lpImageBits, NULL, 0);
	ReleaseDC(NULL, hdcScreen);
	
	// Check
	if(_hbmpHandle == NULL || _hbmpHandle == (HBITMAP)ERROR_INVALID_PARAMETER)
	{
		// Warn, break and return
		LOGE("Could not create DIB section and handle to bitmap for resource %u", _iRes);
		assert(false);
		return NULL;
	}

	// Extract image into HBITMAP
	const UINT iStride = _szSize.cx * 4;
	const UINT iImage = iStride * _szSize.cy;
	if(FAILED(_iwicBMPRes->CopyPixels(NULL, iStride, iImage, static_cast<BYTE*>(lpImageBits))))
	{
		// Delete bitmap
		DeleteObject(_hbmpHandle);
		_hbmpHandle = NULL;

		// Warn, break and return
		LOGE("Could not copy pixels to bitmap for resource %u", _iRes);
		assert(false);
		return NULL;
	}

	// Return
	return _hbmpHandle;
}

PNG::~PNG()
{
	// Release WIC handle
	_iwicBMPRes->Release();

	// Release image stream
	_lpIStream->Release();
}