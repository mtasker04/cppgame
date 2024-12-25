#include <components/Component.h>

#include <components/Transform.h>
#include <GameObject.h>

Component::Component(GameObject& gObject) : gameObject(gObject) {}

GameObject& Component::GetGameObject() const {
	return gameObject;
}
Transform& Component::GetTransform() const {
	return gameObject.GetTransform();
}