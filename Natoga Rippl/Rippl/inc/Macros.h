/************************************************************************/
/* System-Specific Macros                                               */
/************************************************************************/
#ifndef macros_h__
#define macros_h__

// Define windows macro
#if defined(_WIN32) || defined(_WIN64)
#define _WINDOWS
#endif

// Define Tracing Macros
#define LOGV(fmt, ...) TRACE("[VRB] " fmt "\n", __VA_ARGS__)
#define LOGD(fmt, ...) TRACE("[DBG] " fmt "\n", __VA_ARGS__)
#define LOGI(fmt, ...) TRACE("[INF] " fmt "\n", __VA_ARGS__)
#define LOGW(fmt, ...) TRACE("[WRN]> " fmt "\n", __VA_ARGS__)
#define LOGE(fmt, ...) TRACE("[ERR]! " fmt "\n", __VA_ARGS__)

#endif // macros_h__