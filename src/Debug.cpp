#include <Debug.h>

#include <Engine.h>

#include <iostream>

void Debug::Log(const std::string&& message) {
	std::cout << message << std::endl;
}
void Debug::Warn(const std::string&& message) {
	std::cout << "[WARNING] " << message << std::endl;
}
void Debug::Error(const std::string& message, ErrorSeverity severity) {
	if (severity == SEVERITY_FATAL) {
		Engine::Crash(message);
	}
	else {
		std::cout << "[ERROR] " << message;
	}
}