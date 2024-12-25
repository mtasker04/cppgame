#include <Updatable.h>

#include <Engine.h>

Updatable::Updatable() {
	Register();
}

void Updatable::Register() {
	Engine::RegisterUpdatable(this);
}
