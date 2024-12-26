#pragma once

#include <cppgame/Math.h>
#include <cppgame/components/Component.h>

class Transform : public Component
{
public:
	CPPGAPI Transform(GameObject& gameObject);
	CPPGAPI Transform(GameObject& gameObject, Vector2 position, Vector2 rotation, Vector2 scale);

	Vector2 position;
	Vector2 rotation;
	Vector2 scale;

	const Transform* parent;
};