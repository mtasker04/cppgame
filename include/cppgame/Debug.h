#pragma once

#include <cppgame/Generic.h>

#include <string>

typedef unsigned short ErrorSeverity;
#define SEVERITY_FATAL 0x0
#define SEVERITY_LOW 0x1

#ifdef _DEBUG
  #define CGLOG(msg) Debug::Log(msg)
  #define CGWARN(msg) Debug::Warn(msg)
#else
  #define CGLOG(msg)
  #define CGWARN(msg)
#endif
#define CGERR(msg) Debug::Error(msg, SEVERITY_LOW)
#define CGFATAL(msg) Debug::Error(msg, SEVERITY_FATAL)

class Debug
{
public:
	CPPGAPI static void Log(const std::string& message);
	CPPGAPI static void Warn(const std::string& message);
	CPPGAPI static void Error(const std::string& message, ErrorSeverity severity);
};