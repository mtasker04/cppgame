#pragma once

#include <cppgame/Generic.h>
#include <cppgame/rendering/RenderObject.h>

#include <vector>

_INTERNAL class Window;
_INTERNAL class GameRenderer
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