#include <mutex>
#include <thread>
#include "dllhooks.h"
#include "common\common.h"


HMODULE g_user32ModuleHandle = NULL;
const char * USER32_ORIGINAL_NAME = "user32_original.dll";
std::mutex g_moduleHandleMutex;

// REQUIRES: funcPtrType defined
// DEFINES: user32, static funcPtr
#define INTERCEPTION_PROLOGUE(func_name) LOG_STATIC_FUNC(); \
HMODULE user32 = getUser32ModuleHandle(); \
static funcPtrType funcPtr = NULL; \
if (NULL == funcPtr) \
{ \
	funcPtr = (funcPtrType)GetProcAddress(user32, (func_name)); \
} \


HMODULE getUser32ModuleHandle()
{
	if (NULL == g_user32ModuleHandle)
	{
		std::lock_guard<std::mutex> lock(g_moduleHandleMutex);
		if (NULL == g_user32ModuleHandle)
		{
			HMODULE user32ModuleHandle = GetOriginalModuleHandle(USER32_ORIGINAL_NAME);
			if (user32ModuleHandle != NULL)
			{
				g_user32ModuleHandle = user32ModuleHandle;
			}
		}
	}

	return g_user32ModuleHandle;
}


BOOL WINAPI SystemParametersInfoAHook(
	_In_    UINT  uiAction,
	_In_    UINT  uiParam,
	_Inout_ PVOID pvParam,
	_In_    UINT  fWinIni
)
{
	typedef BOOL(WINAPI * funcPtrType)(_In_    UINT  uiAction, _In_    UINT  uiParam, _Inout_ PVOID pvParam, _In_    UINT  fWinIni);

	INTERCEPTION_PROLOGUE("SystemParametersInfoA");
	return funcPtr(uiAction, uiParam, pvParam, fWinIni);
}

BOOL WINAPI GetClientRectHook(
	_In_  HWND   hWnd,
	_Out_ LPRECT lpRect
)
{
	typedef BOOL(WINAPI *funcPtrType)(_In_  HWND   hWnd, _Out_ LPRECT lpRect);
	INTERCEPTION_PROLOGUE("GetClientRect");
	return funcPtr(hWnd, lpRect);
}


BOOL WINAPI ClientToScreenHook(
	_In_    HWND    hWnd,
	_Inout_ LPPOINT lpPoint
)
{
	typedef BOOL(WINAPI *funcPtrType)(_In_    HWND    hWnd,_Inout_ LPPOINT lpPoint);
	INTERCEPTION_PROLOGUE("ClientToScreen");
	return funcPtr(hWnd, lpPoint);
}

LONG WINAPI SetWindowLongWHook(
	_In_ HWND hWnd,
	_In_ int  nIndex,
	_In_ LONG dwNewLong
)
{
	typedef LONG(WINAPI *funcPtrType)(_In_ HWND hWnd,_In_ int  nIndex,_In_ LONG dwNewLong);
	INTERCEPTION_PROLOGUE("SetWindowLongW");
	return funcPtr(hWnd, nIndex, dwNewLong);
}

BOOL WINAPI SetRectHook(
	_Out_ LPRECT lprc,
	_In_  int    xLeft,
	_In_  int    yTop,
	_In_  int    xRight,
	_In_  int    yBottom
)
{
	typedef BOOL(WINAPI *funcPtrType)(_Out_ LPRECT lprc,_In_  int    xLeft,_In_  int    yTop,_In_  int    xRight,_In_  int    yBottom);
	INTERCEPTION_PROLOGUE("SetRect");
	return funcPtr(lprc, xLeft, yTop, xRight, yBottom);
}


HCURSOR WINAPI SetCursorHook(
	_In_opt_ HCURSOR hCursor
)
{
	Log("HI");
	typedef HCURSOR(WINAPI *funcPtrType)(
		_In_opt_ HCURSOR hCursor
		);
	INTERCEPTION_PROLOGUE("SetCursor");
	return funcPtr(hCursor);
}

BOOL WINAPI EnableWindowHook(
	_In_ HWND hWnd,
	_In_ BOOL bEnable
)
{
	typedef BOOL(WINAPI *funcPtrType)(
		_In_ HWND hWnd,
		_In_ BOOL bEnable
		);
	INTERCEPTION_PROLOGUE("EnableWindow");
	return funcPtr(hWnd, bEnable);
}

BOOL WINAPI GetWindowRectHook(
	_In_  HWND   hWnd,
	_Out_ LPRECT lpRect
)
{
	typedef BOOL(WINAPI *funcPtrType)(
		_In_  HWND   hWnd,
		_Out_ LPRECT lpRect
		);
	INTERCEPTION_PROLOGUE("GetWindowRect");
	return funcPtr(hWnd, lpRect);
}

BOOL WINAPI GetClipCursorHook(
	_Out_ LPRECT lpRect
)
{
	typedef BOOL(WINAPI *funcPtrType)(
		_Out_ LPRECT lpRect
		);
	INTERCEPTION_PROLOGUE("GetClipCursor");
	return funcPtr(lpRect);
}

SHORT WINAPI GetAsyncKeyStateHook(
	_In_ int vKey
)
{
	typedef SHORT(WINAPI *funcPtrType)(
		_In_ int vKey
		);
	INTERCEPTION_PROLOGUE("GetAsyncKeyState");
	return funcPtr(vKey);
}

HCURSOR WINAPI LoadCursorAHook(
	_In_opt_ HINSTANCE hInstance,
	_In_     LPCTSTR   lpCursorName
)
{
	typedef HCURSOR(WINAPI *funcPtrType)(
		_In_opt_ HINSTANCE hInstance,
		_In_     LPCTSTR   lpCursorName
		);
	INTERCEPTION_PROLOGUE("LoadCursorA");
	return funcPtr(hInstance, lpCursorName);
}


ATOM WINAPI RegisterClassAHook(
	_In_ const WNDCLASS *lpWndClass
)
{
	typedef ATOM(WINAPI *funcPtrType)(
		_In_ const WNDCLASS *lpWndClass
		);
	INTERCEPTION_PROLOGUE("RegisterClassA");
	return funcPtr(lpWndClass);
}

HWND WINAPI CreateWindowExAHook(
	_In_     DWORD     dwExStyle,
	_In_opt_ LPCTSTR   lpClassName,
	_In_opt_ LPCTSTR   lpWindowName,
	_In_     DWORD     dwStyle,
	_In_     int       x,
	_In_     int       y,
	_In_     int       nWidth,
	_In_     int       nHeight,
	_In_opt_ HWND      hWndParent,
	_In_opt_ HMENU     hMenu,
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ LPVOID    lpParam
)
{
	typedef HWND(WINAPI *funcPtrType)(
		_In_     DWORD     dwExStyle,
		_In_opt_ LPCTSTR   lpClassName,
		_In_opt_ LPCTSTR   lpWindowName,
		_In_     DWORD     dwStyle,
		_In_     int       x,
		_In_     int       y,
		_In_     int       nWidth,
		_In_     int       nHeight,
		_In_opt_ HWND      hWndParent,
		_In_opt_ HMENU     hMenu,
		_In_opt_ HINSTANCE hInstance,
		_In_opt_ LPVOID    lpParam
		);
	INTERCEPTION_PROLOGUE("CreateWindowExA");
	return funcPtr(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

BOOL WINAPI ShowWindowHook(
	_In_ HWND hWnd,
	_In_ int  nCmdShow
)
{
	typedef BOOL(WINAPI *funcPtrType)(
		_In_ HWND hWnd,
		_In_ int  nCmdShow
		);
	INTERCEPTION_PROLOGUE("ShowWindow");
	return funcPtr(hWnd, nCmdShow);
}

BOOL WINAPI UpdateWindowHook(
	_In_ HWND hWnd
)
{
	typedef BOOL(WINAPI *funcPtrType)(_In_ HWND hWnd);
	INTERCEPTION_PROLOGUE("UpdateWindow");
	return funcPtr(hWnd);
}

BOOL WINAPI GetUpdateRectHook(
	_In_  HWND   hWnd,
	_Out_ LPRECT lpRect,
	_In_  BOOL   bErase
)
{
	typedef BOOL(WINAPI *funcPtrType)(
		_In_  HWND   hWnd,
		_Out_ LPRECT lpRect,
		_In_  BOOL   bErase
		);
	INTERCEPTION_PROLOGUE("GetUpdateRect");
	return funcPtr(hWnd, lpRect, bErase);
}

HDC WINAPI BeginPaintHook(
	_In_  HWND          hwnd,
	_Out_ LPPAINTSTRUCT lpPaint
)
{
	typedef HDC(WINAPI *funcPtrType)(
		_In_  HWND          hwnd,
		_Out_ LPPAINTSTRUCT lpPaint
		);
	INTERCEPTION_PROLOGUE("BeginPaint");
	return funcPtr(hwnd, lpPaint);
}

BOOL WINAPI EndPaintHook(
	_In_       HWND        hWnd,
	_In_ const PAINTSTRUCT *lpPaint
)
{
	typedef BOOL(WINAPI *funcPtrType)(
		_In_       HWND        hWnd,
		_In_ const PAINTSTRUCT *lpPaint
		);
	INTERCEPTION_PROLOGUE("EndPaint");
	return funcPtr(hWnd, lpPaint);
}

BOOL WINAPI DestroyWindowHook(
	_In_ HWND hWnd
)
{
	typedef BOOL(WINAPI *funcPtrType)(_In_ HWND hWnd);
	INTERCEPTION_PROLOGUE("DestroyWindow");
	return funcPtr(hWnd);
}

BOOL WINAPI SetWindowPosHook(
	_In_     HWND hWnd,
	_In_opt_ HWND hWndInsertAfter,
	_In_     int  X,
	_In_     int  Y,
	_In_     int  cx,
	_In_     int  cy,
	_In_     UINT uFlags
)
{
	typedef BOOL(WINAPI *funcPtrType)(
		_In_     HWND hWnd,
		_In_opt_ HWND hWndInsertAfter,
		_In_     int  X,
		_In_     int  Y,
		_In_     int  cx,
		_In_     int  cy,
		_In_     UINT uFlags
		);
	INTERCEPTION_PROLOGUE("SetWindowPos");
	return funcPtr(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

BOOL WINAPI AdjustWindowRectExHook(
	_Inout_ LPRECT lpRect,
	_In_    DWORD  dwStyle,
	_In_    BOOL   bMenu,
	_In_    DWORD  dwExStyle
)
{
	typedef BOOL(WINAPI *funcPtrType)(
		_Inout_ LPRECT lpRect,
		_In_    DWORD  dwStyle,
		_In_    BOOL   bMenu,
		_In_    DWORD  dwExStyle
		);
	INTERCEPTION_PROLOGUE("AdjustWindowRectEx");
	return funcPtr(lpRect, dwStyle, bMenu, dwExStyle);
}

LONG WINAPI GetWindowLongAHook(
	_In_ HWND hWnd,
	_In_ int  nIndex
)
{
	typedef LONG(WINAPI *funcPtrType)(
		_In_ HWND hWnd,
		_In_ int  nIndex
		);
	INTERCEPTION_PROLOGUE("");
	return funcPtr(hWnd, nIndex);
}