#include <cppgame/Scene.h>

#include <cppgame/Engine.h>
#include <cppgame/EngineUtils.h>
#include <cppgame/Debug.h>

Scene::Scene(std::string id, const SceneFn& sceneFn)
	: m_SceneFn(sceneFn) {
	if (EngineUtils::StringHasSpaces(id)) {
		CGFATAL("Scene id contains spaces.");
	}
	Register();
}
void Scene::Load() {
	m_SceneFn();
}
void Scene::Unload() {
	this->GetUpdatables().clear();
	this->GetGameObjects().clear();
	this->GetShaders().clear();
	this->GetTextures().clear();
}

void Scene::Register() {
	Engine::RegisterScene(this);
}
