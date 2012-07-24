/************************************************************************/
/* RString Extern Instance/Macro Holder                                 */
/************************************************************************/
#ifndef r_str_h__
#define r_str_h__

// Include
#include "iStringMgr.h"

#include "r_string_mgr.h"

// Macro Def
#define SGETSTRING(id, ...) lpRStrMgr->GetString(id, __VA_ARGS__)

// Declare extern member
extern iStringMgr* lpRStrMgr;

#endif // r_str_h__