#include <cppgame/Updatable.h>

#include <cppgame/Engine.h>

Updatable::Updatable() {
	Register();
}

void Updatable::Register() {
	Engine::RegisterUpdatable(this);
}