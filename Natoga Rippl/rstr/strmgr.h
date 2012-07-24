/************************************************************************/
/* String Manager Implementation                                        */
/************************************************************************/
#ifndef strmgr_h__
#define strmgr_h__

// Includes
#include <Windows.h>

#include "iStringMgr.h"

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