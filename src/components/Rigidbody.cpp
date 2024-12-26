#include <cppgame/components/Rigidbody.h>

#include <cppgame/Settings.h>
#include <cppgame/GameTime.h>
#include <cppgame/GameObject.h>

Rigidbody::Rigidbody(GameObject& obj)
	: Component(obj) {}
Rigidbody::Rigidbody(GameObject& obj, RigidbodyMode mode)
	: Component(obj), mode(mode) {}

void Rigidbody::Update() {
	if (mode == RigidbodyMode::Static) return;
	if (mode != RigidbodyMode::Forceless) {
		velocity += Vector2(0, -(Settings::gravity * gravityScale));
	}
	
	gameObject.GetTransform().position += (velocity * GameTime::GetDeltaTimeSeconds());
}