#pragma once

#include <cppgame/Generic.h>
#include <cppgame/Math.h>
#include <cppgame/components/Component.h>

enum class RigidbodyMode
{
	Dynamic,
	Forceless,
	Static
};
class Rigidbody : public Component
{
public:
	CPPGAPI Rigidbody(GameObject& obj);
	CPPGAPI Rigidbody(GameObject& obj, RigidbodyMode mode);

	RigidbodyMode mode = RigidbodyMode::Dynamic;
	float mass = 1;
	float gravityScale = 1;
	Vector2 velocity;

protected:
	void Update() override;
};