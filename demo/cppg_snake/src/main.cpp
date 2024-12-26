#include <cppgame/Engine.h>

#include "../scripts/TestScript.h"

// Some defines to play around with how the application runs
// and handles different scenarios

//#define DEMO_CREATE_INVALID_TEXTURE 1
//#define DEMO_CREATE_INVALID_SHADER 1

void DemoDefines();

int main()
{
	// Ensure window flags are set before window creation.
	Engine::SetWindowTitle("cppg snake");
	Engine::SetWindowSize(700, 700);

	// Initialize the engine (also creates the window)
	Engine::Init();

	DemoDefines();

	// Create a game scene using a lambda function for scene objects
	Scene* gameScene = new Scene("game_scene", []() {
		GameObject* object = new GameObject("testscript object");
		object->AddComponent<TestScript>();
	});
	// Load the scene at game entry
	Engine::LoadScene(gameScene);

	// Run the engine at the end of initialization
	// This function will not return until the engine has stopped
	Engine::Run();
}

void DemoDefines()
{
#ifdef DEMO_CREATE_INVALID_TEXTURE
	Texture invalidTexture = Texture("InvalidTexture", R"(non_existent_path\invalid_texture.png)");
#endif
#ifdef DEMO_CREATE_INVALID_SHADER
	Shader invalidShader("invalid_shader.vert", "invalid_shader.frag");
#endif
}