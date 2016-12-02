#pragma once

#include <Windows.h>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

static const char * DDRAW_ORIGINAL_NAME = "ddraw_original.dll";
static const char * LOG_FILE_PATH = "log.txt";

HMODULE GetOriginalDDrawModuleHandle(void);

#define IMPL_STDMETHOD(method)        COM_DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE method
#define IMPL_STDMETHOD_(type,method)  COM_DECLSPEC_NOTHROW type STDMETHODCALLTYPE method

// these would only work with a stream
#define DEC(n) std::dec << n
#define HEX(n) std::hex << "0x" << n

#define LOG(s) Log(s)
#define LOG_FORMAT(expr) \
do { \
  stringstream ss; \
  ss << expr; \
  Log(ss.str()); \
} while (0)

#define LOG_THIS_FUNC() LOG_FORMAT(__FILE__ << ":" << __func__ << "[this=" << HEX(this) << "]")
#define LOG_STATIC_FUNC() LOG_FORMAT(__FILE__ << ":" << __func__)

#define LOG_HRESULT(result) LOG_FORMAT(__func__ << ": " << std::hex << result)

void Log(const std::string& message);