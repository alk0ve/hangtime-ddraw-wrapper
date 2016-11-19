#include <ddraw.h>
#include "common.h"

typedef HRESULT (WINAPI * DirectDrawCreateFuncPtr)( GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter );
//char a = &DirectDrawCreate;

HRESULT WINAPI DirectDrawCreateHook(
  _In_  GUID FAR         *lpGUID,
  _Out_ LPDIRECTDRAW FAR *lplpDD,
  _In_  IUnknown FAR     *pUnkOuter
)
{
	HMODULE ddrawModuleHandle = GetOriginalDDrawModuleHandle();
	if (NULL == ddrawModuleHandle)
	{
		OutputDebugString("DirectDrawCreate: failed to find ddraw.dll module handle");
		return DDERR_GENERIC;
	}

	DirectDrawCreateFuncPtr originalDirectDrawCreate = (DirectDrawCreateFuncPtr)GetProcAddress(ddrawModuleHandle,
		"DirectDrawCreate");

	if (NULL == originalDirectDrawCreate)
	{
		OutputDebugString("DirectDrawCreate: failed to find DirectDrawCreate in ddraw.dll");
		return DDERR_GENERIC;
	}

	return originalDirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
}