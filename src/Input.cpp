#include <Input.h>

bool Input::IsKeyDown(Key key)
{
	return keyStates[(int)key];
}
bool Input::IsKeyPressed(Key key)
{
	return keyStates[(int)key] && !keyStatesPrev[(int)key];
}
bool Input::IsKeyReleased(Key key)
{
	return !keyStates[(int)key] && keyStatesPrev[(int)key];
}

void Input::Update()
{
	for (int i = 0; i < (int)Key::Count; i++)
	{
		keyStatesPrev[i] = keyStates[i];
		keyStates[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

bool Input::keyStates[(int)Key::Count];
bool Input::keyStatesPrev[(int)Key::Count];