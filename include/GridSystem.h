#pragma once

#include <Generic.h>
#include <Settings.h>

class GridSystem
{
public:
	static int NPCScale2PCScale(float npcScale, bool height = false);
	static float PCScale2NPCScale(int pcScale, bool height = false);
	static int GridScale2PCScale(float gridScale);
};