#include <mutex>
#include <thread>
#include "dllhooks.h"
#include "common\common.h"


HMODULE g_user32ModuleHandle = NULL;
const char * USER32_ORIGINAL_NAME = "user32_original.dll";
std::mutex g_moduleHandleMutex;

// REQUIRES: funcPtrType defined
// DEFINES: user32, funcPtr
#define INTERCEPTION_PROLOGUE(func_name) HMODULE user32 = getUser32ModuleHandle(); \
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
);

LONG WINAPI SetWindowLongWHook(
	_In_ HWND hWnd,
	_In_ int  nIndex,
	_In_ LONG dwNewLong
);

BOOL WINAPI SetRectHook(
	_Out_ LPRECT lprc,
	_In_  int    xLeft,
	_In_  int    yTop,
	_In_  int    xRight,
	_In_  int    yBottom
);


HCURSOR WINAPI SetCursorHook(
	_In_opt_ HCURSOR hCursor
);

BOOL WINAPI EnableWindowHook(
	_In_ HWND hWnd,
	_In_ BOOL bEnable
);

BOOL WINAPI GetWindowRectHook(
	_In_  HWND   hWnd,
	_Out_ LPRECT lpRect
);

BOOL WINAPI GetClipCursorHook(
	_Out_ LPRECT lpRect
);

SHORT WINAPI GetAsyncKeyStateHook(
	_In_ int vKey
);

HCURSOR WINAPI LoadCursorAHook(
	_In_opt_ HINSTANCE hInstance,
	_In_     LPCTSTR   lpCursorName
);


ATOM WINAPI RegisterClassAHook(
	_In_ const WNDCLASS *lpWndClass
);

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
);

BOOL WINAPI ShowWindowHook(
	_In_ HWND hWnd,
	_In_ int  nCmdShow
);

BOOL WINAPI UpdateWindowHook(
	_In_ HWND hWnd
);

BOOL WINAPI GetUpdateRectHook(
	_In_  HWND   hWnd,
	_Out_ LPRECT lpRect,
	_In_  BOOL   bErase
);

HDC WINAPI BeginPaintHook(
	_In_  HWND          hwnd,
	_Out_ LPPAINTSTRUCT lpPaint
);

BOOL WINAPI EndPaintHook(
	_In_       HWND        hWnd,
	_In_ const PAINTSTRUCT *lpPaint
);

BOOL WINAPI DestroyWindowHook(
	_In_ HWND hWnd
);

BOOL WINAPI SetWindowPosHook(
	_In_     HWND hWnd,
	_In_opt_ HWND hWndInsertAfter,
	_In_     int  X,
	_In_     int  Y,
	_In_     int  cx,
	_In_     int  cy,
	_In_     UINT uFlags
);

BOOL WINAPI AdjustWindowRectExHook(
	_Inout_ LPRECT lpRect,
	_In_    DWORD  dwStyle,
	_In_    BOOL   bMenu,
	_In_    DWORD  dwExStyle
);

LONG WINAPI GetWindowLongAHook(
	_In_ HWND hWnd,
	_In_ int  nIndex
);