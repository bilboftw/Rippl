/************************************************************************/
/* WinMain Function                                                     */
/*   Windows only!                                                      */
/************************************************************************/

// Includes
#include <windows.h>

#include "Macros.h"

#include "rippl.hpp"
#include "resource.h"
#include "strmgr.h"
#include "tween_engine.h"

void onevent(Tween* t, R_TWEEN_CB_MSG msg)
{
	switch(msg)
	{
	case START:
		LOGI("Starting tween!");
		break;
	case TICK:
		LOGI("Tick: %u", t->GetPercentComplete());
		break;
	case FINISH:
		LOGI("Tween finished!");
		TerminateRippl(0);
		break;
	}
}

/**
 * WinMain Function
 *	Main Windows program entry point
 */
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Initialize Resources
	InitResources(hInstance);

	// DEBUG: Message Box
	MessageBoxW(NULL, StringMgr::Get()->GetString(R_DEBUG_MSG), StringMgr::Get()->GetString(R_TITLE), MB_OK);

	Tween* twn = new Tween();
	twn->lDelay = 1000;
	twn->lDuration = 3000;
	twn->cbOnEvent = &onevent;

	TweenEngine::Get()->Add(twn);

	while(true){Sleep(1);}
	
	// Release Resources
	ReleaseResources();

	// Return Success
	return 0;
}