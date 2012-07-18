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

	const char*						GetString(UINT dwStringID, ...);
protected:
	static StringMgr*				_oMgr;
private:
	StringMgr() {};
	~StringMgr() {};

	static bool						_bCreated;
};

#endif // strmgr_h__