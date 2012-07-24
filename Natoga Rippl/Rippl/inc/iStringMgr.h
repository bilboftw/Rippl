/************************************************************************/
/* String Manager Interface                                             */
/************************************************************************/
#ifndef iStringMgr_h__
#define iStringMgr_h__


// String Manager Interface
class iStringMgr
{
public:
	virtual const wchar_t*		GetString(unsigned int dwStringID, ...) = 0;
};

#endif // iStringMgr_h__