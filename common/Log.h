#pragma once
#include "common.h"

using std::string;
using std::stringstream;

static const char * LOG_FILE_PATH = "log.txt";

// these would only work with a stream
#define DEC(n) std::dec << (n)
#define HEX(n) std::hex << "0x" << (n)

void Log(const std::string& message);

#ifndef DISABLE_LOG
#define LOG(s) Log((s))
#define LOG_FORMAT(expr) \
do { \
	stringstream ss; \
	ss << expr; \
	Log(ss.str()); \
} while (0)

#define LOG_THIS_FUNC() LOG_FORMAT(__FILE__ << ":" << __func__ << "[this=" << HEX(this) << "]")
#define LOG_STATIC_FUNC() LOG_FORMAT(__FILE__ << ":" << __func__)

#define LOG_HRESULT(result) LOG_FORMAT(__func__ << ": " << std::hex << (result))

#else // DISABLE_LOG is defined
#define DO_NOTHING do {} while (0)

#define LOG(s) DO_NOTHING
#define LOG_FORMAT(expr) DO_NOTHING

#define LOG_THIS_FUNC() DO_NOTHING
#define LOG_STATIC_FUNC() DO_NOTHING

#define LOG_HRESULT(result) DO_NOTHING
#endif



