#pragma once

#include <cppgame/Generic.h>
#include <cppgame/GameObject.h>
#include <cppgame/IHeapManaged.h>
#include <cppgame/rendering/Shader.h>
#include <cppgame/rendering/Texture.h>

#include <functional>

typedef std::function<void()> SceneFn;

class Scene : public IHeapManaged
{
public:
	CPPGAPI Scene(std::string id, const SceneFn& sceneFn);

	CPPGAPI void Load();
	CPPGAPI void Unload();

	std::vector<Updatable*>& GetUpdatables() { return m_Updatables; }
	std::vector<GameObject*>& GetGameObjects() { return m_GObjects; }
	std::vector<Shader*>& GetShaders() { return m_Shaders; }
	std::vector<Texture*>& GetTextures() { return m_Textures; }

public:
	void Register() override;

private:
	std::string m_SceneId;
	SceneFn m_SceneFn;

	std::vector<Updatable*> m_Updatables;
	std::vector<GameObject*> m_GObjects;
	std::vector<Shader*> m_Shaders;
	std::vector<Texture*> m_Textures;
};