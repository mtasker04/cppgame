#include <Window.h>

#include <Debug.h>
#include <Engine.h>
#include <Input.h>
#include <rendering/GameRenderer.h>

#include <GLFW/glfw3.h>

Window::Window(const char* title, int width, int height)
	: m_WindowTitle(title) {
	m_Width = width;
	m_Height = height;
	if (!Init()) {
		return;
	}
	CGLOG("[WINDOW] Window created successfully");
	m_Renderer = new GameRenderer(this);
	CGLOG("[WINDOW] Renderer created successfully");
}
Window::~Window() {
	delete m_Renderer;
}

void Window::Update() {
	if (Input::IsKeyPressed(Key::F)) {
		ToggleFullscreen();
	}
	if (m_Renderer) {
		m_Renderer->Clear();
	}
}
void Window::Render() {
	if (m_Renderer) {
		m_Renderer->Render();
	}
}
void Window::Close() {
	glfwDestroyWindow(m_WndPtr);
	glfwTerminate();
}

void Window::ToggleFullscreen() {
	m_Fullscreen = !m_Fullscreen;

	if (m_Fullscreen) {
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
		m_WindowedWidth = m_Width;
		m_WindowedHeight = m_Height;
		m_Width = mode->width;
		m_Height = mode->height;
		glfwSetWindowMonitor(m_WndPtr, primaryMonitor, 0, 0, m_Width, m_Height, mode->refreshRate);
	}
	else {
		m_Width = m_WindowedWidth;
		m_Height = m_WindowedHeight;
		glfwSetWindowMonitor(m_WndPtr, nullptr, 100, 100, m_Width, m_Height, 0);
	}
}

void Window::PollEvents() const {
	glfwPollEvents();
}
bool Window::ShouldClose() const {
	return glfwWindowShouldClose(m_WndPtr);
}

bool Window::Init() {
	if (!glfwInit()) {
		CGFATAL("Failed to initialize GLFW.");
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_WndPtr = glfwCreateWindow(m_Width, m_Height, m_WindowTitle, NULL, NULL);
	if (!m_WndPtr) {
		CGFATAL("Failed to create window.");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_WndPtr);

	glfwSetWindowUserPointer(m_WndPtr, this);

	glfwSetFramebufferSizeCallback(m_WndPtr, WindowResize);

	return true;
}

void Window::WindowResize(GLFWwindow* wnd, int width, int height) {
	Window* window = static_cast<Window*>(glfwGetWindowUserPointer(wnd));
	window->m_Width = width;
	window->m_Height = height;
	glViewport(0, 0, width, height);
}