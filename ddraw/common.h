#pragma once

#include <Windows.h>
#include <string>

static const char * DDRAW_ORIGINAL_NAME = "ddraw_original.dll";
static const char * LOG_FILE_PATH = "log.txt";

HMODULE GetOriginalDDrawModuleHandle(void);

void Log(const std::string& message);