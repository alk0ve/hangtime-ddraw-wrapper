#include "common.h"

HMODULE GetOriginalDDrawModuleHandle(void)
{
	HMODULE ddrawModule = GetModuleHandle(DDRAW_ORIGINAL_NAME);
	if (NULL == ddrawModule)
	{
		// the module is not yet loaded - let's load it then
		// this might cause original_ddraw.dll to have a reference count of one higher than it should,
		// but since it's only released when the process closes it's not an issue
		ddrawModule = LoadLibrary(DDRAW_ORIGINAL_NAME);
		if (NULL == ddrawModule)
		{
			OutputDebugString("GetOriginalDDrawModuleHandle: failed to retrieve ddraw.dll module handle");
		}
	}

	return ddrawModule;
}
