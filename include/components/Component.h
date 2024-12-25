#pragma once

#include <Generic.h>

#include <Updatable.h>

#include <memory>

class GameObject;
class Transform;
class Component : protected Updatable
{
public:
	Component(GameObject& gObject);

	CPPGAPI GameObject& GetGameObject() const;
	CPPGAPI Transform& GetTransform() const;

protected:
	GameObject& gameObject;
};