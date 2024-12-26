#include <cppgame/components/Collider.h>

#include <cppgame/Debug.h>

#include <iostream>
#include <sstream>

#undef min
#undef max

std::vector<Collider*> Collider::m_Colliders;

Collider::Collider(GameObject& obj)
	: Component(obj), scale(obj.GetTransform().scale), offset(Vector2::Zero),
	m_WorldPosition(GetTransform().position + offset),
	m_Bounds(Bounds(m_WorldPosition - (scale / 2), m_WorldPosition + (scale / 2))) {
	m_Colliders.push_back(this);
}
Collider::Collider(GameObject& obj, Vector2 scale, Vector2 offset)
	: Component(obj), scale(scale), offset(offset),
	m_WorldPosition(gameObject.GetTransform().position + offset),
	m_Bounds(Bounds(m_WorldPosition - (scale / 2), m_WorldPosition + (scale / 2))) {
	m_Colliders.push_back(this);
}

void Collider::Update() {
	m_WorldPosition = gameObject.GetTransform().position + offset;
	m_Bounds = Bounds(m_WorldPosition - (scale / 2), m_WorldPosition + (scale / 2));
	CheckCollisions();
}
void Collider::CheckCollisions() {
	for (Collider* c : m_Colliders) {
		if (c == this) continue;
		if (m_Bounds.Intersects(c->m_Bounds)) {
			std::ostringstream oss;
			oss << gameObject.GetName() << " Collided with: " << c->GetGameObject().GetName() << std::endl;
			CGLOG(oss.str());
			//ResolveCollision(c);
		}
	}
}
void Collider::ResolveCollision(Collider* other) {
	
	m_WorldPosition = gameObject.GetTransform().position + offset;
	m_Bounds = Bounds(m_WorldPosition - (scale / 2), m_WorldPosition + (scale / 2));
}