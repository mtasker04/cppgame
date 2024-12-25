#pragma once

#include <Generic.h>
#include <rendering/RenderObject.h>

#include <vector>

class Window;
class GameRenderer
{
public:
	GameRenderer(Window* gameWindow);
	~GameRenderer();

	CPPGAPI void BindObject(RenderObject* renderObject);

	CPPGAPI void Clear();

	CPPGAPI void Render();

private:
	std::vector<RenderObject*> m_RenderObjects;
};