#include <fstream>
#include "Log.h"


HANDLE g_logMutexHandle = CreateMutex(NULL, FALSE, "HangtimeLogMutex");


class MutexAutoRelease
{
public:
	MutexAutoRelease(HANDLE mutexHandle)
		: m_mutexHandle(mutexHandle)
	{}
	~MutexAutoRelease()
	{
		ReleaseMutex(m_mutexHandle);
	}

private:
	HANDLE m_mutexHandle;
};


void Log(const std::string& message)
{
#ifndef DISABLE_LOG
	if (NULL == g_logMutexHandle)
	{
		OutputDebugString("ERROR: NULL == g_logMutexHandle");
		return;
	}
	
	DWORD result = WaitForSingleObject(g_logMutexHandle, INFINITE);
	if (WAIT_OBJECT_0 != result)
	{
		OutputDebugString("ERROR: WAIT_OBJECT_0 != result");
		return;
	}

	std::ofstream log_file(LOG_FILE_PATH,
		std::ios_base::out | std::ios_base::app);
	log_file << message << std::endl;
#endif
}
