#include <fstream>
#include <mutex>
#include <thread>
#include "Log.h"


std::mutex g_logMutex;


void Log(const std::string& message)
{
#ifndef DISABLE_LOG

	std::lock_guard<std::mutex> lock(g_logMutex);

	std::ofstream log_file(LOG_FILE_PATH,
		std::ios_base::out | std::ios_base::app);
	log_file << message << std::endl;
#endif
}
