#include <physics/Bounds.h>

#undef min
#undef max

Bounds::Bounds(const Vector2& min, const Vector2& max)
	: min(min), max(max) {}

bool Bounds::Intersects(const Bounds& other) const {
	return	min.x <= other.max.x && max.x >= other.min.x &&
		min.y <= other.max.y && max.y >= other.min.y;
}
bool Bounds::Contains(const Vector2& point) const {
	return	point.x >= min.x && point.x <= max.x &&
		point.y >= min.y && point.y <= max.y;
}