#include <Scene.h>

#include <Engine.h>
#include <EngineUtils.h>
#include <Debug.h>

Scene::Scene(std::string id, const SceneFn& sceneFn)
	: m_SceneFn(sceneFn) {
	if (EngineUtils::StringHasSpaces(id)) {
		CGFATAL("Scene id contains spaces.");
	}
	Engine::RegisterScene(this);
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