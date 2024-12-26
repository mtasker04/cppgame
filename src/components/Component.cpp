#include <cppgame/components/Component.h>

#include <cppgame/GameObject.h>
#include <cppgame/components/Transform.h>

Component::Component(GameObject& gObject) : gameObject(gObject) {}

GameObject& Component::GetGameObject() const {
	return gameObject;
}
Transform& Component::GetTransform() const {
	return gameObject.GetTransform();
}