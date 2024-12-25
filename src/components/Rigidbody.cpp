#include <components/Rigidbody.h>

#include <Settings.h>
#include <GameTime.h>
#include <GameObject.h>

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