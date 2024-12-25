#include <Engine.h>

#include <Debug.h>
#include <Input.h>
#include <GTime.h>
#include <Window.h>
#include <GameObject.h>
#include <components/Collider.h>
#include <components/Transform.h>

#include <iostream>

Engine::~Engine() {
	delete m_GameWindow;
}

void Engine::RegisterUpdatable(Updatable* updatable) {
	m_CurrentScene->GetUpdatables().push_back(updatable);
}
void Engine::RegisterGameObject(GameObject* gObject) {
	m_CurrentScene->GetGameObjects().push_back(gObject);
}
void Engine::RegisterShader(Shader* shader) {
	m_CurrentScene->GetShaders().push_back(shader);
}
void Engine::RegisterTexture(Texture* texture) {
	m_CurrentScene->GetTextures().push_back(texture);
}
void Engine::RegisterScene(Scene* scene) {
	m_Scenes.push_back(scene);
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
	Time::Start();
	for (Updatable* updatable : m_CurrentScene->GetUpdatables()) {
		if (!updatable) {
			CGFATAL("Failed to start engine (ES_UPDATABLE_NULLPTR)");
		}
		updatable->Start();
	}
	m_Running = true;
}
void Engine::Update() {
	Time::Update();
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
		oss << "Frame Time: " << Time::GetDeltaTimeSeconds() << "s" << "\n";
		oss << "Estimated FPS: " << 1.0f / Time::GetDeltaTimeSeconds() << "fps";
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
	for (Scene* scene : m_Scenes) {
		scene->Unload();
		delete scene;
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

std::vector<Scene*> Engine::m_Scenes;
Scene* Engine::m_CurrentScene = nullptr;
bool Engine::m_Running = false;
std::string Engine::m_WindowTitle = "Game Window";
Vector2 Engine::m_WindowSize = Vector2(800, 600);
Window* Engine::m_GameWindow = nullptr;
Camera* Engine::m_CurrentCamera = nullptr;