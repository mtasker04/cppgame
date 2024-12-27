#pragma once

#include <cppgame/Generic.h>

#include <string>

class Math
{
public:
	CPPGAPI static int Abs(int value);
	CPPGAPI static float Abs(float value);
	CPPGAPI static int AbsRef(int& valueref);
	CPPGAPI static float AbsRef(float& valueref);
	CPPGAPI static int Clamp(int value, int min, int max);
	CPPGAPI static float Clamp(float value, float min, float max);
	CPPGAPI static int ClampRef(int& valueref, int min, int max);
	CPPGAPI static float ClampRef(float& valueref, float min, float max);
	CPPGAPI static float Lerp(float a, float b, float t);
	CPPGAPI static float InverseLerp(float a, float b, float value);
};

class Vector2
{
public:
	float x, y;

	CPPGAPI Vector2();
	CPPGAPI Vector2(float x, float y);

	CPPGAPI static Vector2 Zero;
	CPPGAPI static Vector2 One;
	CPPGAPI static Vector2 Lerp(Vector2 a, Vector2 b, float t);
	CPPGAPI static Vector2 InverseLerp(Vector2 a, Vector2 b, float t);

	CPPGAPI float Magnitude() const;
	CPPGAPI Vector2 Normalized() const;

	CPPGAPI Vector2 operator+(const Vector2& other);
	CPPGAPI Vector2 operator-(const Vector2& other);
	CPPGAPI Vector2 operator*(const Vector2& other);
	CPPGAPI Vector2 operator/(const Vector2& other);
	CPPGAPI Vector2 operator*(const float& other);
	CPPGAPI Vector2 operator/(const float& other);
	CPPGAPI Vector2 operator+=(const Vector2& other);
	CPPGAPI Vector2 operator-=(const Vector2& other);
	CPPGAPI Vector2 operator*=(const Vector2& other);
	CPPGAPI Vector2 operator/=(const Vector2& other);
	CPPGAPI Vector2 operator*=(const float& other);
	CPPGAPI Vector2 operator/=(const float& other);
	CPPGAPI bool operator==(const Vector2& other);
	CPPGAPI bool operator!=(const Vector2& other);

	CPPGAPI std::string Str() const;
};