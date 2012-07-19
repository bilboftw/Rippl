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
}

IStream* PNG::GetIStream()
{
	// Find resource and check
	HRSRC hrRes = FindResource(NULL, MAKEINTRESOURCE(_iRes), MAKEINTRESOURCE(_iRes));
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