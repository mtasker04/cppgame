#include <cppgame/EngineUtils.h>

bool EngineUtils::StringHasSpaces(const std::string& id) {
	for (size_t i = 0; i < id.length(); i++) {
		if (id[i] == ' ') {
			return true;
		}
	}
	return false;
}