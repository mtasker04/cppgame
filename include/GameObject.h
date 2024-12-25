#pragma once

#include <Generic.h>
#include <components/Component.h>
#include <components/Transform.h>

#include <vector>
#include <string>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <stdexcept>

class GameObject
{
public:
	CPPGAPI GameObject(std::string name);
	CPPGAPI GameObject(std::string name, Vector2 position, Vector2 rotation, Vector2 scale);
	CPPGAPI ~GameObject();

	CPPGAPI Transform& GetTransform() const;

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args);

	template<typename T>
	void RemoveComponent();

	template<typename T>
	T* const GetComponent();

	CPPGAPI const std::string& GetName() const;
	CPPGAPI void SetName(std::string name);

public:
	CPPGAPI static GameObject CreateRect(std::string name);

private:
	void Register();

	std::string m_Name;
	std::vector<Component*> m_Components;
};

template<typename T, typename... Args>
T& GameObject::AddComponent(Args&&... args) {
	static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
	auto component = new T(*this, std::forward<Args>(args)...);
	T& ref = *component;
	m_Components.push_back(std::move(component));
	return ref;
}

template<typename T>
void GameObject::RemoveComponent() {
	static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
	m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(),
		[](const Component* component) {
			return dynamic_cast<T*>(component) != nullptr;
		}), m_Components.end());
}

template<typename T>
T* const GameObject::GetComponent() {
	static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
	for (auto& component : m_Components) {
		if (auto derived = dynamic_cast<T*>(component)) {
			return derived;
		}
	}
	return nullptr;
}