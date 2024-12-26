#include <cppgame/GridSystem.h>

#include <cppgame/Engine.h>

int GridSystem::NPCScale2PCScale(float npcScale, bool height)
{
	float hNPCScale = npcScale / 2;
	int multiplier = height ? Engine::GetWindow()->GetHeight() : Engine::GetWindow()->GetWidth();
	return static_cast<int>(hNPCScale * multiplier);
}
float GridSystem::PCScale2NPCScale(int pcScale, bool height)
{
	int divider = height ? Engine::GetWindow()->GetHeight() : Engine::GetWindow()->GetWidth();
	divider /= 2;
	return float(pcScale) / float(divider);
}
int GridSystem::GridScale2PCScale(float gridScale)
{
	return static_cast<int>(gridScale * (Settings::gridScale * Engine::GetCurrentCamera()->GetZoom()));
}