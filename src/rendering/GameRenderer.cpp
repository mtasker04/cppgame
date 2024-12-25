#include <rendering/GameRenderer.h>

#include <Debug.h>
#include <Engine.h>
#include <Window.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

GameRenderer::GameRenderer(Window* gameWindow) {
	CGLOG("[GameRenderer] Initializing GLAD");
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		CGFATAL("Failed to initialize GLAD.");
		return;
	}

	CGLOG("[GameRenderer] Setting viewport");
	glViewport(0, 0, gameWindow->GetWidth(), gameWindow->GetHeight());
}
GameRenderer::~GameRenderer() {
	for (RenderObject* renderObject : m_RenderObjects) {
		delete renderObject;
	}
}

void GameRenderer::BindObject(RenderObject* renderObject) {
	m_RenderObjects.push_back(renderObject);
	CGLOG("[GameRenderer] Bound object");
	std::ostringstream oss;
	oss << "[GameRenderer] Render objects size: " << m_RenderObjects.size();
	CGLOG(oss.str());
}

void GameRenderer::Clear() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	CGLOG("[GameRenderer] Screen cleared");
}

void GameRenderer::Render() {
	CGLOG("[GameRenderer] Begin rendering");
	for (RenderObject* renderObject : m_RenderObjects) {
		CGLOG("[GameRenderer] Drawing object");
		renderObject->Draw();
	}
	CGLOG("[GameRenderer] Clearing render objects");
	m_RenderObjects.clear();

	CGLOG("[GameRenderer] Swapping buffers");
	glfwSwapBuffers(Engine::GetWindow()->GetWndPtr());
	CGLOG("[GameRenderer] Polling events");
	glfwPollEvents();
	CGLOG("[GameRenderer] End rendering");
}