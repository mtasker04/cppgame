#include <cppgame/Engine.h>

#include <cppgame/Debug.h>
#include <cppgame/Input.h>
#include <cppgame/GameTime.h>
#include <cppgame/Window.h>
#include <cppgame/GameObject.h>
#include <cppgame/components/Collider.h>
#include <cppgame/components/Transform.h>

#include <iostream>

Engine::~Engine() {
	delete m_GameWindow;
}

void Engine::RegisterUpdatable(Updatable* updatable) {
	m_CurrentScene->GetUpdatables().push_back(updatable);
	AddManaged(dynamic_cast<IHeapManaged*>(updatable));
}
void Engine::RegisterGameObject(GameObject* gObject) {
	m_CurrentScene->GetGameObjects().push_back(gObject);
	AddManaged(dynamic_cast<IHeapManaged*>(gObject));
}
void Engine::RegisterShader(Shader* shader) {
	m_CurrentScene->GetShaders().push_back(shader);
	AddManaged(dynamic_cast<IHeapManaged*>(shader));
}
void Engine::RegisterTexture(Texture* texture) {
	m_CurrentScene->GetTextures().push_back(texture);
	AddManaged(dynamic_cast<IHeapManaged*>(texture));
}
void Engine::RegisterScene(Scene* scene) {
	m_Scenes.push_back(scene);
	AddManaged(dynamic_cast<IHeapManaged*>(scene));
}

void Engine::Init() {
	InitWindow();
}
void Engine::Run() {
	Start();
	while (IsRunning()) {
		Update();
		Render();
	}
}

void Engine::Start() {
	CGLOG("[ENGINE] Engine starting");
	GameTime::Start();
	for (Updatable* updatable : m_CurrentScene->GetUpdatables()) {
		if (!updatable) {
			CGFATAL("Failed to start engine (ES_UPDATABLE_NULLPTR)");
		}
		updatable->Start();
	}
	m_Running = true;
}
void Engine::Update() {
	GameTime::Update();
	Input::Update();
	for (Updatable* loop : m_CurrentScene->GetUpdatables()) {
		loop->Update();
	}
	m_GameWindow->Update();
}
void Engine::Render() {
	if (m_CurrentCamera) {
		for (Updatable* loop : m_CurrentScene->GetUpdatables()) {
			loop->Render();
		}
		m_GameWindow->Render();

		std::ostringstream oss;
		oss << "Frame GameTime: " << GameTime::GetDeltaTimeSeconds() << "s" << "\n";
		oss << "Estimated FPS: " << 1.0f / GameTime::GetDeltaTimeSeconds() << "fps";
		CGLOG(oss.str());
	}
	else CGWARN("[ENGINE] No camera is active, rendering will be skipped");
	
	m_GameWindow->PollEvents();
	if (m_GameWindow->ShouldClose()) {
		m_GameWindow->Close();
		Stop();
	}
}
void Engine::Stop() {
	CGLOG("[ENGINE] Engine stopping");
	Shutdown();
	m_Running = false;
}
void Engine::Shutdown() {
	for (IHeapManaged* managed : m_ManagedObjects) {
		delete managed;
	}
}
void Engine::Crash(const std::string& message) {
	if (m_Running) Stop();
	MessageBox(NULL, message.c_str(), "Fatal Error", MB_OK | MB_ICONERROR);
	exit(EXIT_FAILURE);
}
bool Engine::IsRunning() {
	return m_Running;
}

void Engine::SetWindowTitle(const std::string& title) {
	m_WindowTitle = title;
}
void Engine::SetWindowSize(int width, int height) {
	m_WindowSize = Vector2((float)width, (float)height);
}

Window* Engine::GetWindow() {
	return m_GameWindow;
}

void Engine::SetCurrentCamera(Camera* cam) {
	m_CurrentCamera = cam;
}
Camera* const Engine::GetCurrentCamera() {
	return m_CurrentCamera;
}

void Engine::LoadScene(Scene* scene) {
	if (m_CurrentScene) {
		m_CurrentScene->Unload();
	}
	m_CurrentScene = scene;
	m_CurrentScene->Load();
}

void Engine::InitWindow() {
	m_GameWindow = new Window(m_WindowTitle.c_str(), (int)m_WindowSize.x, (int)m_WindowSize.y);
}

void Engine::AddManaged(IHeapManaged* managed) {
	m_ManagedObjects.push_back(managed);
}

std::vector<Scene*> Engine::m_Scenes;
std::vector<IHeapManaged*> Engine::m_ManagedObjects;
Scene* Engine::m_CurrentScene = nullptr;
bool Engine::m_Running = false;
std::string Engine::m_WindowTitle = "Game Window";
Vector2 Engine::m_WindowSize = Vector2(800, 600);
Window* Engine::m_GameWindow = nullptr;
Camera* Engine::m_CurrentCamera = nullptr;