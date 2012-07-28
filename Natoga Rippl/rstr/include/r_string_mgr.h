/************************************************************************/
/* Rippl String Manager                                                 */
/************************************************************************/
#ifndef r_string_mgr_h__
#define r_string_mgr_h__

// Includes
#include "ROutput.h"

#include "r_string_id.h"
#include "iStringMgr.h"

// Define imports
extern "C" __declspec(dllimport) iStringMgr* __stdcall MGS(ROutputHandler** rohOutputHandler);


#endif // r_string_mgr_h__