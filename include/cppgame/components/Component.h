#pragma once

#include <cppgame/Generic.h>
#include <cppgame/Updatable.h>

#include <memory>

_INTERNAL class GameObject;
_INTERNAL class Transform;
_INTERNAL class Component : protected Updatable
{
public:
	Component(GameObject& gObject);

	CPPGAPI GameObject& GetGameObject() const;
	CPPGAPI Transform& GetTransform() const;

protected:
	GameObject& gameObject;
};