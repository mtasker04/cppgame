#pragma once

#include <cppgame/Generic.h>

class Color
{
public:
	CPPGAPI Color();
	CPPGAPI Color(float r, float g, float b, float a = 1.0f);

	void ToFloatArray(float* arr) const;

	float r, g, b, a;
};