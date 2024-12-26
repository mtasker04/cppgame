#include <cppgame/types/Color.h>

Color::Color()
	: r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
Color::Color(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a) {}

void Color::ToFloatArray(float* arr) const {
	arr[0] = r;
	arr[1] = g;
	arr[2] = b;
	arr[3] = a;
}