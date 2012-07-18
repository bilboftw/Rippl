/************************************************************************/
/* String Manager Implementation                                        */
/************************************************************************/
#ifndef strmgr_h__
#define strmgr_h__

// Includes
#include "iStringMgr.h"

// String Manager Class Definition
class StringMgr : public iStringMgr
{
public:
	static StringMgr*				Get();

	const char*						GetString(DWORD dwStringID, ...);
private:
	StringMgr();
	~StringMgr();
};

#endif // strmgr_h__