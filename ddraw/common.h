#pragma once

#include <Windows.h>

static const char * DDRAW_ORIGINAL_NAME = "ddraw_original.dll";

HMODULE GetOriginalDDrawModuleHandle(void);