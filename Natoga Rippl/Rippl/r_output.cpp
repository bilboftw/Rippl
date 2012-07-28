/************************************************************************/
/* Rippl Output/Debugging Output Functionality                          */
/************************************************************************/

// Includes
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>

#include "r_output.h"

// Static Defines
ROutputHandler* ROutput::Handler;

void ROutput::Init()
{
	// Create new instance
	Handler = new ROutput();
}

void ROutput::SetOutputHandler(ROutputHandler* oNewHandler)
{
	// Get handle window
	HWND hwndCur = Handler->GetAssociatedWindow();

	// Get clone current handler
	ROutputHandler* lpCur = Handler;

	// Set hwnd for new handler
	oNewHandler->SetAssociatedWindow(hwndCur);

	// Set handler
	Handler = oNewHandler;

	// Delete old handler
	delete lpCur;
}

void ROutput::Uninstall()
{
	// Delete handler
	delete Handler;
}

ROutput::ROutput()
{
	// Setup NULL window handler
	_hwndAssociatedHandler = NULL;

#if defined(_DEBUG) && defined(_WINDOWS_)
	// Attempt to allocate console
	if(AllocConsole())
	{
		// Get the info / Set the scroll-buffer
		CONSOLE_SCREEN_BUFFER_INFO coninfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
		coninfo.dwSize.Y = 2000;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

		// Redirect STDOUT
		long lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
		int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		FILE* fp = _fdopen(hConHandle, "w");
		*stdout = *fp;
		setvbuf(stdin, NULL, _IONBF, 0);

		// Redirect STDERR
		lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
		fp = _fdopen( hConHandle, "w" );
		*stderr = *fp;
		setvbuf( stderr, NULL, _IONBF, 0 );

		// Sync with STDIO
		std::ios::sync_with_stdio();
	}
#endif
}

ROutput::~ROutput()
{
#if defined(_DEBUG) && defined(_WINDOWS_)
	// Free Console
	FreeConsole();
#endif
}

R_OP_MSG_ID ROutput::DisplayMessage(const wchar_t* szMsg, bool bYesNo /* = false */, bool bCancellable /* = false */, ...)
{
	// Construct Message
	wchar_t szProcessed[2048];
	va_list vaList;
	va_start(vaList, bCancellable);
	wvsprintfW((wchar_t*)&szProcessed, szMsg, vaList);
	va_end(vaList);

	// Construct Flags
#ifdef _WINDOWS_
	UINT iFlags = (bCancellable ? (bYesNo ? MB_YESNOCANCEL : MB_OKCANCEL) : (bYesNo ? MB_YESNO : MB_OK)) | MB_ICONINFORMATION;
#endif

	// Display message
#ifdef _WINDOWS_
	return (R_OP_MSG_ID) MessageBoxW(_hwndAssociatedHandler, (wchar_t*)&szProcessed, L"Rippl", iFlags);
#endif
}

R_OP_MSG_ID ROutput::DisplayMessage(const char* szMsg, bool bYesNo /* = false */, bool bCancellable /* = false */, ...)
{
	// Construct Message
	char szProcessed[2048];
	va_list vaList;
	va_start(vaList, bCancellable);
	vsprintf_s((char*)&szProcessed, sizeof(szProcessed), szMsg, vaList);
	va_end(vaList);

	// Construct Flags
#ifdef _WINDOWS_
	UINT iFlags = (bCancellable ? (bYesNo ? MB_YESNOCANCEL : MB_OKCANCEL) : (bYesNo ? MB_YESNO : MB_OK)) | MB_ICONINFORMATION;
#endif

	// Display message
#ifdef _WINDOWS_
	return (R_OP_MSG_ID) MessageBoxA(_hwndAssociatedHandler, (char*)&szProcessed, "Rippl", iFlags);
#endif
}

R_OP_MSG_ID ROutput::DisplayError(const char* szMsg, bool bYesNo /* = false */, bool bCancellable /* = false */, ...)
{
	// Construct Message
	char szProcessed[2048];
	va_list vaList;
	va_start(vaList, bCancellable);
	vsprintf_s((char*)&szProcessed, sizeof(szProcessed), szMsg, vaList);
	va_end(vaList);

	// Construct Flags
#ifdef _WINDOWS_
	UINT iFlags = (bCancellable ? (bYesNo ? MB_YESNOCANCEL : MB_OKCANCEL) : (bYesNo ? MB_YESNO : MB_OK)) | MB_ICONERROR;
#endif

	// Break
#if defined(_WINDOWS_) && defined(_DEBUG)
	DebugBreak();
#endif

	// Display message
#ifdef _WINDOWS_
	return (R_OP_MSG_ID) MessageBoxA(_hwndAssociatedHandler, (char*)&szProcessed, "Rippl", iFlags);
#endif
}

R_OP_MSG_ID ROutput::DisplayError(const wchar_t* szMsg, bool bYesNo /* = false */, bool bCancellable /* = false */, ...)
{
	// Construct Message
	wchar_t szProcessed[2048];
	va_list vaList;
	va_start(vaList, bCancellable);
	wvsprintfW((wchar_t*)&szProcessed, szMsg, vaList);
	va_end(vaList);

	// Construct Flags
#ifdef _WINDOWS_
	UINT iFlags = (bCancellable ? (bYesNo ? MB_YESNOCANCEL : MB_OKCANCEL) : (bYesNo ? MB_YESNO : MB_OK)) | MB_ICONERROR;
#endif

	// Break
#if defined(_WINDOWS_) && defined(_DEBUG)
	DebugBreak();
#endif

	// Display message
#ifdef _WINDOWS_
	return (R_OP_MSG_ID) MessageBoxW(_hwndAssociatedHandler, (wchar_t*)&szProcessed, L"Rippl", iFlags);
#endif
}

void ROutput::PrintMsg(const char* szMsg, ...)
{
	// Construct Message
	char szProcessed[2048];
	va_list vaList;
	va_start(vaList, szMsg);
	vsprintf_s((char*)&szProcessed, sizeof(szProcessed), szMsg, vaList);
	va_end(vaList);

	// Just print
	vprintf_s((char*)&szProcessed, vaList);
}

void ROutput::PrintDbgMsg(const char* szMsg, ...)
{
	// Construct Message
	char szProcessed[2048];
	va_list vaList;
	va_start(vaList, szMsg);
	vsprintf_s((char*)&szProcessed, sizeof(szProcessed), szMsg, vaList);
	va_end(vaList);

	// Just print
	vprintf_s((char*)&szProcessed, vaList);
}

void ROutput::SetAssociatedWindow(HWND hwndHandle /* = NULL */)
{
	// Assign
	_hwndAssociatedHandler = hwndHandle;
}

HWND ROutput::GetAssociatedWindow()
{
	// Return
	return _hwndAssociatedHandler;
}