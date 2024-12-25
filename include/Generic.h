#pragma once

// These keywords do nothing and are purely for code readability
#define INTERNAL
#define STATIC
#define _INTERFACE class

#define ENGINE_NAME cppg
#define ENGINE_NAME_CSTR "cppg"

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef CPPG_BUILD_DLL
#define CPPGAPI __declspec(dllexport)
#else
#define CPPGAPI __declspec(dllimport)
#endif