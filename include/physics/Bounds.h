#pragma once

#include <Generic.h>
#include <GMath.h>

class Bounds
{
public:
	CPPGAPI Bounds(const Vector2& min, const Vector2& max);

	CPPGAPI bool Intersects(const Bounds& other) const;
	CPPGAPI bool Contains(const Vector2& point) const;

	Vector2 min;
	Vector2 max;
};