#pragma once

#include <Generic.h>

_EXTERNAL struct GLFWwindow;
class Engine;
_INTERNAL class GameRenderer;
_INTERNAL class Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	void Update();
	void Render();
	CPPGAPI void Close();

	CPPGAPI int GetWidth() const { return m_Width; }
	CPPGAPI int GetHeight() const { return m_Height; }

	void ToggleFullscreen();

	void PollEvents() const;
	bool ShouldClose() const;

	GameRenderer* GetRenderer() const { return m_Renderer; }
	GLFWwindow* GetWndPtr() const { return m_WndPtr; }

private:
	bool Init();

	static void WindowResize(GLFWwindow* window, int width, int height);

	const char* m_WindowTitle;
	const char* m_WindowId;
	int m_Width, m_Height;
	int m_WindowedWidth, m_WindowedHeight;
	bool m_Fullscreen;
	GameRenderer* m_Renderer;
	GLFWwindow* m_WndPtr;
};