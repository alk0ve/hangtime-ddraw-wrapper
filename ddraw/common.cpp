#include "common.h"

HMODULE GetOriginalDDrawModuleHandle(void)
{
	HMODULE ddrawModule = GetModuleHandle(DDRAW_ORIGINAL_NAME);
	if (NULL == ddrawModule)
	{
		// the module is not yet loaded - let's load it then
		ddrawModule = LoadLibrary(DDRAW_ORIGINAL_NAME);
		if (NULL == ddrawModule)
		{
			OutputDebugString("GetOriginalDDrawModuleHandle: failed to retrieve ddraw.dll module handle");
		}
	}

	return ddrawModule;
}