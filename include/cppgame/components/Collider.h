#pragma once

#include <cppgame/Generic.h>
#include <cppgame/Math.h>
#include <cppgame/GameObject.h>
#include <cppgame/physics/Bounds.h>
#include <cppgame/components/Component.h>

class Collider : public Component
{
public:
	CPPGAPI Collider(GameObject& obj);
	CPPGAPI Collider(GameObject& obj, Vector2 scale, Vector2 offset);

	bool isTrigger = false;

	Vector2 offset;
	Vector2 scale;

private:
	Vector2 m_WorldPosition;
	Bounds m_Bounds;

	static std::vector<Collider*> m_Colliders;

	void Update() override;
	void CheckCollisions();
	void ResolveCollision(Collider* other);
};