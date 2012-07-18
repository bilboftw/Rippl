/************************************************************************/
/* PrintF to Output Window                                              */
/************************************************************************/
#ifndef OPrintF_h__
#define OPrintF_h__

// Includes
#include <iostream>

// Define Function
void oprintf(const char* fmt, ...)
{
	// Create VA List
	va_list valList;
	va_start(valList, fmt);

	// Create String Buffer
	char szBuf[1024];

	// Convert string
	vsprintf_s((char*)&szBuf, sizeof(szBuf), fmt, valList);

	// Output
	OutputDebugStr((char*)&szBuf);

	// Kill VA List
	va_end(valList);
}

#endif // OPrintF_h__