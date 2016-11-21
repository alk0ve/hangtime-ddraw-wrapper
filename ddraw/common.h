#pragma once

#include <Windows.h>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

static const char * DDRAW_ORIGINAL_NAME = "ddraw_original.dll";
static const char * LOG_FILE_PATH = "log.txt";

HMODULE GetOriginalDDrawModuleHandle(void);

#define LOG(s) Log(s)
#define LOG_FORMAT(expr) \
do { \
  stringstream ss; \
  ss << expr; \
  Log(ss.str()); \
} while (0)

#define LOG_FUNC() Log(__func__)

#define LOG_HRESULT(result) LOG_FORMAT(__func__ << ": " << std::hex << result)

void Log(const std::string& message);