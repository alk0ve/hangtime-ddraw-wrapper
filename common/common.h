#pragma once

#include <Windows.h>
#include <string>
#include <sstream>
#include "Log.h"


HMODULE GetOriginalModuleHandle(const char * moduleName);

#define IMPL_STDMETHOD(method)        COM_DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE method
#define IMPL_STDMETHOD_(type,method)  COM_DECLSPEC_NOTHROW type STDMETHODCALLTYPE method
