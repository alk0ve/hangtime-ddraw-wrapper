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
	stringstream ss;
	ss << "DirectDrawCreate(" << lpGUID << ", " << lplpDD << ", " << pUnkOuter << ")";
	Log(ss.str());


	HMODULE ddrawModuleHandle = GetOriginalDDrawModuleHandle();
	if (NULL == ddrawModuleHandle)
	{
		Log("DirectDrawCreate: failed to find ddraw.dll module handle");
		return DDERR_GENERIC;
	}

	DirectDrawCreateFuncPtr originalDirectDrawCreate = (DirectDrawCreateFuncPtr)GetProcAddress(ddrawModuleHandle,
		"DirectDrawCreate");

	if (NULL == originalDirectDrawCreate)
	{
		Log("DirectDrawCreate: failed to find DirectDrawCreate in ddraw.dll");
		return DDERR_GENERIC;
	}

	HRESULT result = originalDirectDrawCreate(lpGUID, lplpDD, pUnkOuter);
	LOG_HRESULT(result);
	return result;
}