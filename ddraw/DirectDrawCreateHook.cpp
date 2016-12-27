#include <ddraw.h>
#include "common/common.h"
#include "MyIDirectDraw.h"

typedef HRESULT (WINAPI * DirectDrawCreateFuncPtr)( GUID FAR *lpGUID, LPDIRECTDRAW FAR *lplpDD, IUnknown FAR *pUnkOuter );
const char * DDRAW_ORIGINAL_NAME = "ddraw_original.dll";

HRESULT WINAPI DirectDrawCreateHook(
  _In_  GUID FAR         *lpGUID,
  _Out_ LPDIRECTDRAW FAR *lplpDD,
  _In_  IUnknown FAR     *pUnkOuter
)
{
	stringstream ss;
	ss << "DirectDrawCreate(" << lpGUID << ", " << lplpDD << ", " << pUnkOuter << ")";
	Log(ss.str());


	HMODULE ddrawModuleHandle = GetOriginalModuleHandle(DDRAW_ORIGINAL_NAME);
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

	LPDIRECTDRAW realDirectDrawPtr = NULL;

	HRESULT result = originalDirectDrawCreate(lpGUID, &realDirectDrawPtr, pUnkOuter);
	LOG_HRESULT(result);

	if (DD_OK == result)
	{
		MyIDirectDraw * myIDirectDraw = new MyIDirectDraw(realDirectDrawPtr);
		*lplpDD = myIDirectDraw;
		LOG_FORMAT("Returning MyIDirectDraw at " << HEX(myIDirectDraw));
	}

	return result;
}