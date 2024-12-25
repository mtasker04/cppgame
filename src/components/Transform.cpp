#include <components/Transform.h>

Transform::Transform(GameObject& gameObject)
	: Component(gameObject), position(Vector2::Zero), rotation(Vector2::Zero), scale(Vector2::One), parent(nullptr) {}
Transform::Transform(GameObject& gameObject, Vector2 position, Vector2 rotation, Vector2 scale)
	: Component(gameObject), position(position), rotation(rotation), scale(scale), parent(nullptr) {}