/************************************************************************/
/* PrintF to Output Window                                              */
/************************************************************************/

// Include
#include <Windows.h>
#include <iostream>

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