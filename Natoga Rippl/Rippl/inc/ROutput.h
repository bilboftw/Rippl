/************************************************************************/
/* Rippl Output/Debugging Output Functionality                          */
/*                                                                      */
/*  The Pod Lib version of this interface needs to be updated whenever  */
/*  updates are made to the interface (only the interface)!!            */
/************************************************************************/
#ifndef r_output_h__
#define r_output_h__

// Includes
#include <windows.h>

// Messagebox Return Definitions
enum R_OP_MSG_ID
{
	RMI_OK = IDOK,
	RMI_CANCEL = IDCANCEL,
	RMI_YES = IDYES,
	RMI_NO = IDNO
};

// Output Handler Interface
interface ROutputHandler
{
public:
	virtual R_OP_MSG_ID				DisplayMessage(const wchar_t* szMsg, bool bYesNo = false, bool bCancellable = false, ...) = 0;
	virtual R_OP_MSG_ID				DisplayMessage(const char* szMsg, bool bYesNo = false, bool bCancellable = false, ...) = 0;
	virtual R_OP_MSG_ID				DisplayError(const wchar_t* szMsg, bool bYesNo = false, bool bCancellable = false, ...) = 0;
	virtual R_OP_MSG_ID				DisplayError(const char* szMsg, bool bYesNo = false, bool bCancellable = false, ...) = 0;
	
	virtual void					PrintMsg(const char* szMsg, ...) = 0;
	virtual void					PrintDbgMsg(const char* szMsg, ...) = 0;
};

// Host handler interface
//	Adds window association methods that aren't used
//	by parts of the program such as pods.
interface RHostOutputHandler : public ROutputHandler
{
public:
	virtual void					SetAssociatedWindow(HWND hwndHandle = NULL) = 0;
	virtual HWND					GetAssociatedWindow() = 0;
};

class ROutput : public RHostOutputHandler
{
public:
	ROutput();
	~ROutput();

	static void						Init();
	static void						SetOutputHandler(RHostOutputHandler* oNewHandler);
	static void						Uninstall();

	R_OP_MSG_ID						DisplayMessage(const wchar_t* szMsg, bool bYesNo = false, bool bCancellable = false, ...);
	R_OP_MSG_ID						DisplayMessage(const char* szMsg, bool bYesNo = false, bool bCancellable = false, ...);
	R_OP_MSG_ID						DisplayError(const wchar_t* szMsg, bool bYesNo = false, bool bCancellable = false, ...);
	R_OP_MSG_ID						DisplayError(const char* szMsg, bool bYesNo = false, bool bCancellable = false, ...);

	void							PrintMsg(const char* szMsg, ...);
	void							PrintDbgMsg(const char* szMsg, ...);

	void							SetAssociatedWindow(HWND hwndHandle = NULL);
	HWND							GetAssociatedWindow();

	static ROutputHandler*			Handler;

protected:
	HWND							_hwndAssociatedHandler;
};

#endif // r_output_h__