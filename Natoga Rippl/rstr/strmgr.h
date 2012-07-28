/************************************************************************/
/* String Manager Implementation                                        */
/************************************************************************/
#ifndef strmgr_h__
#define strmgr_h__

// Includes
#include <Windows.h>

#include "ROutput.h"
#include "iStringMgr.h"

// Static handle to output
extern ROutputHandler** rohHandler;

// Define Log Functions
#define LOGV(fmt, ...) (*rohHandler)->PrintDbgMsg(fmt "\n", __VA_ARGS__)
#define LOGD(fmt, ...) (*rohHandler)->PrintDbgMsg("> " fmt "\n", __VA_ARGS__)
#define LOGI(fmt, ...) (*rohHandler)->PrintMsg(fmt "\n", __VA_ARGS__)
#define LOGW(fmt, ...) (*rohHandler)->PrintMsg("! " fmt "\n", __VA_ARGS__)
#define LOGE(fmt, ...) {(*rohHandler)->PrintMsg("!! " fmt "\n", __VA_ARGS__); (*rohHandler)->DisplayError(fmt, false, false, __VA_ARGS__);}

// String Manager Class Definition
class StringMgr : public iStringMgr
{
public:
	static void						Init(HINSTANCE hinstInst);
	static StringMgr*				Get();

	const wchar_t*					GetString(UINT dwStringID, ...);
protected:
	static StringMgr*				_oMgr;
private:
	StringMgr() {};
	~StringMgr() {};

	static HINSTANCE				_hinstMainApp;
	static bool						_bCreated;
};

#endif // strmgr_h__