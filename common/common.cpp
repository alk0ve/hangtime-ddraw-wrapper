#include "common.h"

HMODULE GetOriginalDDrawModuleHandle(const char * moduleName)
{
	HMODULE ddrawModule = GetModuleHandle(moduleName);
	if (NULL == ddrawModule)
	{
		// the module is not yet loaded - let's load it then
		// this might cause original_ddraw.dll to have a reference count of one higher than it should,
		// but since it's only released when the process closes it's not an issue
		ddrawModule = LoadLibrary(moduleName);
		if (NULL == ddrawModule)
		{
			LOG_FORMAT("GetOriginalDDrawModuleHandle: failed to retrieve module handle for " << moduleName);
		}
	}

	return ddrawModule;
}
