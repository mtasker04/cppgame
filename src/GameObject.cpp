#include <cppgame/GameObject.h>

#include <cppgame/Debug.h>
#include <cppgame/Engine.h>
#include <cppgame/components/Renderer.h>

#include <iostream>

GameObject::GameObject(std::string name)
	: m_Name(name) {
	m_Components.push_back(new Transform(*this));
	Register();
}
GameObject::GameObject(std::string name, Vector2 position, Vector2 rotation, Vector2 scale)
	: m_Name(name) {
	m_Components.push_back(new Transform(*this, position, rotation, scale));
	Register();
}
GameObject::~GameObject() {
	for (Component* component : m_Components) {
		delete component;
	}
}

Transform& GameObject::GetTransform() const {
	if (auto transform = dynamic_cast<Transform*>(m_Components[0])) {
		return *transform;
	}
	CGFATAL("GameObject is missing a required transform component.");
}

const std::string& GameObject::GetName() const {
	return m_Name;
}
void GameObject::SetName(std::string name) {
	m_Name = name;
}

CPPGAPI GameObject GameObject::CreateRect(std::string name) {
	GameObject obj = GameObject(name);
	obj.AddComponent<Renderer>(RendererMode::Rect);
	return obj;
}

void GameObject::Register() {
	Engine::RegisterGameObject(this);
}