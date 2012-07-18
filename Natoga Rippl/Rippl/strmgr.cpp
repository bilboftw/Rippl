/************************************************************************/
/* String Manager Implementation                                        */
/************************************************************************/

// Includes
#include <windows.h>
#include <iostream>

#include "Macros.h"

#include "strmgr.h"

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

const char* StringMgr::GetString(UINT dwStringID, ...)
{
	// Get message
	CString cstrMsg;

	// Check
	if(!cstrMsg.LoadString(dwStringID))
	{
		LOGE("Could not retrieve message ID %u", dwStringID);
		ASSERT(false);
		return NULL;
	}

	// Set up VA List
	va_list valList;
	va_start(valList, dwStringID);

	// Set up string pointer
	LPTSTR lpszTemp;

	// Format and Check
	if(
		FormatMessage(	FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
						cstrMsg,
						0,
						0,
						(LPTSTR)&lpszTemp,
						0,
						&valList
						) == 0)
	{
		// Log, break and return original message
		LOGW("Could not format string %u", dwStringID);
		ASSERT(FALSE);
		return (LPCSTR)cstrMsg;
	}
	
	// Destroy VA List
	va_end(valList);

	// Return
	return lpszTemp;
}