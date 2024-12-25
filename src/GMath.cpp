#include <GMath.h>

#include <sstream>

int Math::Clamp(int value, int min, int max) {
	return (value > max) ? max : (value < min) ? min : value;
}
float Math::Clamp(float value, float min, float max) {
	return (value > max) ? max : (value < min) ? min : value;
}
float Math::Lerp(float a, float b, float t) {
	return a + (b - a) * t;
}
float Math::InverseLerp(float a, float b, float value) {
	return (value - a) / (b - a);
}

Vector2::Vector2()
	: x(0), y(0) {}
Vector2::Vector2(float x, float y)
	: x(x), y(y) {}

Vector2 Vector2::Zero = Vector2(0, 0);
Vector2 Vector2::One = Vector2(1, 1);
Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t) {
	return Vector2(Math::Lerp(a.x, b.x, t), Math::Lerp(a.y, b.y, t));
}
Vector2 Vector2::InverseLerp(Vector2 a, Vector2 b, float t) {
	return Vector2(Math::InverseLerp(a.x, b.x, t), Math::InverseLerp(a.y, b.y, t));
}

float Vector2::Magnitude() const {
	return sqrt(x * x + y * y);
}
Vector2 Vector2::Normalized() const {
	float mag = Magnitude();
	return Vector2(x / mag, y / mag);
}

Vector2 Vector2::operator+(const Vector2& other) {
	return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2& other) {
	return Vector2(x - other.x, y - other.y);
}
Vector2 Vector2::operator*(const Vector2& other) {
	return Vector2(x * other.x, y * other.y);
}
Vector2 Vector2::operator/(const Vector2& other) {
	return Vector2(x / other.x, y / other.y);
}
Vector2 Vector2::operator*(const float& other) {
	return Vector2(x * other, y * other);
}
Vector2 Vector2::operator/(const float& other) {
	return Vector2(x / other, y / other);
}
Vector2 Vector2::operator+=(const Vector2& other) {
	x += other.x, y += other.y; return *this;
}
Vector2 Vector2::operator-=(const Vector2& other) {
	x -= other.x, y -= other.y; return *this;
}
Vector2 Vector2::operator*=(const Vector2& other) {
	x *= other.x, y *= other.y; return *this;
}
Vector2 Vector2::operator/=(const Vector2& other) {
	x /= other.x, y /= other.y; return *this;
}
Vector2 Vector2::operator*=(const float& other) {
	x *= other, y *= other; return *this;
}
Vector2 Vector2::operator/=(const float& other) {
	x /= other, y /= other; return *this;
}
bool Vector2::operator==(const Vector2& other) {
	return x == other.x && y == other.y;
}
bool Vector2::operator!=(const Vector2& other) {
	return x != other.x || y != other.y;
}

std::string Vector2::Str() const {
	std::ostringstream oss;
	oss << "(";
	oss << x << ", ";
	oss << y << ")";
	return oss.str();
}