/************************************************************************/
/* Rippl Pod Output Interface                                           */
/*                                                                      */
/*  The pod is passed a pointer to a pointer of an interface object     */
/*  which is used to output messages to the user through the host       */
/*  application.                                                        */
/*                                                                      */
/*  NOTE: Do not dereference the pointer to pointer. The object's       */
/*        lifetime is not guaranteed! Sometimes, especially during load */
/*        times, the output handler will change!                        */
/************************************************************************/
#ifndef IOutput_h__
#define IOutput_h__

// Includes
#include <Windows.h>

/**
 * Message Box Return IDs
 */
enum R_OP_MSG_ID
{
	RMI_OK = IDOK,
	RMI_CANCEL = IDCANCEL,
	RMI_YES = IDYES,
	RMI_NO = IDNO
};

/**
 * Rippl output interface
 */
interface IOutputHandler
{
public:
	/**
	 * Displays a message in the form of a message box
	 *	to the user
	 *
	 *	Returns which button was pressed
	 *	
	 *	This function has printf-like argument functionality
	 */
	virtual R_OP_MSG_ID				DisplayMessage(const wchar_t* szMsg, bool bYesNo = false, bool bCancellable = false, ...) = 0;
	virtual R_OP_MSG_ID				DisplayMessage(const char* szMsg, bool bYesNo = false, bool bCancellable = false, ...) = 0;

	/**
	 * Displays an error in the form of a message box
	 *	to the user
	 *
	 *	Returns which button was pressed
	 *	
	 *	This function has printf-like argument functionality
	 *	NOTE:	This function will raise a debug breakpoint if
	 *			debug mode is enabled!
	 */
	virtual R_OP_MSG_ID				DisplayError(const wchar_t* szMsg, bool bYesNo = false, bool bCancellable = false, ...) = 0;
	virtual R_OP_MSG_ID				DisplayError(const char* szMsg, bool bYesNo = false, bool bCancellable = false, ...) = 0;
	
	/**
	 * Prints a message to the current output stream
	 *	
	 *	NOTE:	This function does not show any sort of output
	 *			to the user - it shows up either in the allocated console
	 *			or the in-host console (when Rippl enters the graphical mode)
	 */
	virtual void					PrintMsg(const char* szMsg, ...) = 0;

	/**
	 * Prints a debug message to the current output stream
	 *	
	 *	NOTE:	This function does not show any sort of output
	 *			to the user - it shows up either in the allocated console
	 *			or the in-host console (when Rippl enters the graphical mode)
	 */
	virtual void					PrintDbgMsg(const char* szMsg, ...) = 0;
};

#endif // IOutput_h__