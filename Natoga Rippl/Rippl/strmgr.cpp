/************************************************************************/
/* String Manager Implementation                                        */
/************************************************************************/

// Includes
#include <windows.h>
#include <iostream>

#include "Macros.h"
#include "OPrintF.hpp"

#include "strmgr.h"

// Static Member Definitions
HINSTANCE StringMgr::_hinstMainApp = NULL;
StringMgr* StringMgr::_oMgr = NULL;
bool StringMgr::_bCreated = false;

void StringMgr::Init(HINSTANCE hinstInst)
{
	// Store instance
	_hinstMainApp = hinstInst;
}

StringMgr* StringMgr::Get()
{
	// Check if we've created or not
	if(!_bCreated)
	{
		// Create and signal
		_oMgr = new StringMgr();
		_bCreated = true;
	}

	// Return
	return _oMgr;
}

const wchar_t* StringMgr::GetString(UINT dwStringID, ...)
{
	// Get String and Check
	wchar_t szBuf[4096];
	if(LoadStringW(_hinstMainApp, dwStringID, (LPWSTR)&szBuf, sizeof(szBuf) / sizeof(wchar_t)) == 0)
	{
		// Log, break and return
		LOGE("Resource ID %u could not be loaded: %u", dwStringID, GetLastError());
		assert(false);
		return NULL;
	}

	// Set up VA List
	va_list valList;
	va_start(valList, dwStringID);

	// Set up string pointer
	LPWSTR lpszTemp = NULL;

	// Format and Check
	if(
		FormatMessageW(	FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
						(LPWSTR)&szBuf,
						0,
						0,
						(LPWSTR)&lpszTemp,
						0,
						&valList
						) == 0)
	{
		// Log, break and return original message
		LOGW("Could not format string %u: %u", dwStringID, GetLastError());
		assert(FALSE);
	}
	
	// Destroy VA List
	va_end(valList);

	// Return
	return lpszTemp;
}