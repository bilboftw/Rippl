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
	// Set up VA List
	va_list valList;
	va_start(valList, dwStringID);

	// Set up string pointer
	LPWSTR lpszTemp = NULL;

	// Format and Check
	if(
		FormatMessageW(	FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER,
						_hinstMainApp,
						dwStringID,
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