/************************************************************************/
/* System-Specific Macros                                               */
/************************************************************************/
#ifndef macros_h__
#define macros_h__

// Includes
#include "OPrintF.h"

#ifdef _DEBUG
#include "assert.h"
#else
#define assert(cond)
#endif

// Define Tracing Macros
#define LOGV(fmt, ...) oprintf("[VRB] " fmt "\n", __VA_ARGS__)
#define LOGD(fmt, ...) oprintf("[DBG] " fmt "\n", __VA_ARGS__)
#define LOGI(fmt, ...) oprintf("[INF] " fmt "\n", __VA_ARGS__)
#define LOGW(fmt, ...) oprintf("[WRN]> " fmt "\n", __VA_ARGS__); assert(false)
#define LOGE(fmt, ...) oprintf("[ERR]! " fmt "\n", __VA_ARGS__); assert(false)

#endif // macros_h__