#include "common.h"
#include <fstream>
#include <mutex>
#include <thread>


std::mutex g_logMutex;


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


void Log(const std::string& message)
{
	std::lock_guard<std::mutex> lock(g_logMutex);

    std::ofstream log_file(LOG_FILE_PATH,
						   std::ios_base::out | std::ios_base::app);
    log_file << message << std::endl;
}