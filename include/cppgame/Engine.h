#pragma once

#include <cppgame/Generic.h>
#include <cppgame/Updatable.h>
#include <cppgame/GameObject.h>
#include <cppgame/Window.h>
#include <cppgame/Scene.h>
#include <cppgame/components/Camera.h>
#include <cppgame/rendering/Shader.h>
#include <cppgame/rendering/Texture.h>

#include <vector>
#include <memory>

class Engine
{
public:
	~Engine();

	static void RegisterUpdatable(Updatable* updatable);
	static void RegisterGameObject(GameObject* gObject);
	static void RegisterShader(Shader* shader);
	static void RegisterTexture(Texture* texture);
	static void RegisterScene(Scene* scene);

	CPPGAPI static void Init();
	CPPGAPI static void Run();

	static void Start();
	static void Update();
	static void Render();
	static void Stop();
	static void Shutdown();
	static void Crash(const std::string& message);
	CPPGAPI static bool IsRunning();

	CPPGAPI static void SetWindowTitle(const std::string& title);
	CPPGAPI static void SetWindowSize(int width, int height);

	static Window* GetWindow();

	CPPGAPI static void SetCurrentCamera(Camera* cam);
	CPPGAPI static Camera* const GetCurrentCamera();

	CPPGAPI static void LoadScene(Scene* scene);

private:
	Engine();
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	static void InitWindow();

	static void AddManaged(IHeapManaged* managed);

	static std::vector<Scene*> m_Scenes;
	static std::vector<IHeapManaged*> m_ManagedObjects;
	static Scene* m_CurrentScene;
	static bool m_Running;
	static std::string m_WindowTitle;
	static Vector2 m_WindowSize;
	static Window* m_GameWindow;
	static Camera* m_CurrentCamera;
};