/************************************************************************/
/* System-Specific Macros                                               */
/************************************************************************/
#ifndef macros_h__
#define macros_h__

// Includes
#include "r_output.h"

// Define Tracing Macros
#define LOGV(fmt, ...) ROutput::Handler->PrintDbgMsg(fmt "\n", __VA_ARGS__)
#define LOGD(fmt, ...) ROutput::Handler->PrintDbgMsg("> " fmt "\n", __VA_ARGS__)
#define LOGI(fmt, ...) ROutput::Handler->PrintMsg(fmt "\n", __VA_ARGS__)
#define LOGW(fmt, ...) ROutput::Handler->PrintMsg("! " fmt "\n", __VA_ARGS__)
#define LOGE(fmt, ...) {ROutput::Handler->PrintMsg("!! " fmt "\n", __VA_ARGS__); ROutput::Handler->DisplayError(fmt, false, false, __VA_ARGS__);}

#endif // macros_h__