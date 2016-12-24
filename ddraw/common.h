#pragma once

#include <Windows.h>
#include <string>
#include <sstream>
#include "Log.h"


static const char * DDRAW_ORIGINAL_NAME = "ddraw_original.dll";

HMODULE GetOriginalDDrawModuleHandle(void);

#define IMPL_STDMETHOD(method)        COM_DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE method
#define IMPL_STDMETHOD_(type,method)  COM_DECLSPEC_NOTHROW type STDMETHODCALLTYPE method
