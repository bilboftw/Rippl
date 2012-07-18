/************************************************************************/
/* String Manager Interface                                             */
/************************************************************************/
#ifndef iStringMgr_h__
#define iStringMgr_h__

// String Manager Interface
interface iStringMgr
{
public:
	virtual const wchar_t*		GetString(UINT dwStringID, ...) = 0;
};

#endif // iStringMgr_h__