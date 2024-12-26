#pragma once

#include <cppgame/Generic.h>
#include <cppgame/Settings.h>

_INTERNAL class GridSystem
{
public:
	static int NPCScale2PCScale(float npcScale, bool height = false);
	static float PCScale2NPCScale(int pcScale, bool height = false);
	static int GridScale2PCScale(float gridScale);
};