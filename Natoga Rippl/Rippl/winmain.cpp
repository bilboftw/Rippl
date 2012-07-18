/************************************************************************/
/* WinMain Function                                                     */
/*   Windows only!                                                      */
/************************************************************************/

// Includes
#include <windows.h>

#include "rippl.hpp"

/**
 * WinMain Function
 *	Main Windows program entry point
 */
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// DEBUG: Message Box
	MessageBox(NULL, "Hello, Qix.\n\nWelcome to Rippl.", "Rippl", MB_OK);

	// Release Resources
	ReleaseResources();

	// Return Success
	return 0;
}