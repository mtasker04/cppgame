#pragma once

#include <cppgame/Generic.h>
#include <cppgame/Updatable.h>
#include <cppgame/Math.h>

#include <Xinput.h>

enum class Key
{
	Unknown = -1,
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	Zero = 0x30,
	One = 0x31,
	Two = 0x32,
	Three = 0x33,
	Four = 0x34,
	Five = 0x35,
	Six = 0x36,
	Seven = 0x37,
	Eight = 0x38,
	Nine = 0x39,
	Escape = VK_ESCAPE,
	LControl = VK_LCONTROL,
	LShift = VK_LSHIFT,
	LAlt = VK_LMENU,
	LSystem = VK_LWIN,
	RControl = VK_RCONTROL,
	RShift = VK_RSHIFT,
	RAlt = VK_RMENU,
	RSystem = VK_RWIN,
	Menu = VK_APPS,
	LBracket = VK_OEM_4,
	RBracket = VK_OEM_6,
	SemiColon = VK_OEM_1,
	Comma = VK_OEM_COMMA,
	Period = VK_OEM_PERIOD,
	Quote = VK_OEM_7,
	Slash = VK_OEM_2,
	BackSlash = VK_OEM_5,
	Tilde = VK_OEM_3,
	Equal = VK_OEM_PLUS,
	Dash = VK_OEM_MINUS,
	Space = VK_SPACE,
	Return = VK_RETURN,
	BackSpace = VK_BACK,
	Tab = VK_TAB,
	PageUp = VK_PRIOR,
	PageDown = VK_NEXT,
	End = VK_END,
	Home = VK_HOME,
	Insert = VK_INSERT,
	Delete = VK_DELETE,
	Add = VK_ADD,
	Subtract = VK_SUBTRACT,
	Multiply = VK_MULTIPLY,
	Divide = VK_DIVIDE,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	Up = VK_UP,
	Down = VK_DOWN,
	NumpadZero = VK_NUMPAD0,
	NumpadOne = VK_NUMPAD1,
	NumpadTwo = VK_NUMPAD2,
	NumpadThree = VK_NUMPAD3,
	NumpadFour = VK_NUMPAD4,
	NumpadFive = VK_NUMPAD5,
	NumpadSix = VK_NUMPAD6,
	NumpadSeven = VK_NUMPAD7,
	NumpadEight = VK_NUMPAD8,
	NumpadNine = VK_NUMPAD9,
	F1 = VK_F1,
	F2 = VK_F2,
	F3 = VK_F3,
	F4 = VK_F4,
	F5 = VK_F5,
	F6 = VK_F6,
	F7 = VK_F7,
	F8 = VK_F8,
	F9 = VK_F9,
	F10 = VK_F10,
	F11 = VK_F11,
	F12 = VK_F12,
	F13 = VK_F13,
	F14 = VK_F14,
	F15 = VK_F15,
	Pause = VK_PAUSE,
	Count = 102
};
enum class MouseButton
{
	Left = VK_LBUTTON,
	Right = VK_RBUTTON,
	Middle = VK_MBUTTON,
	XButton1 = VK_XBUTTON1,
	XButton2 = VK_XBUTTON2,
	Count = 5
};

enum class ControllerButton
{
	DPadUp = 0x0001,
	DPadDown = 0x0002,
	DPadLeft = 0x0004,
	DPadRight = 0x0008,
	Start = 0x0010,
	Back = 0x0020,
	JoystickLeft = 0x0040,
	JoystickRight = 0x80,
	ShoulderLeft = 0x0100,
	ShoulderRight = 0x0200,
	A = 0x1000,
	B = 0x2000,
	X = 0x4000,
	Y = 0x8000,
	Count = 14
};
enum class ControllerAxis
{
	JoystickLeftX,
	JoystickLeftY,
	JoystickRightX,
	JoystickRightY,
	TriggerLeft,
	TriggerRight,
	Count = 6
};
enum class ControllerMotor
{
	Left,
	Right,
	Count = 2
};
enum class ControllerID
{
	One = 0,
	Two = 1,
	Three = 2,
	Four = 3,
	Count = 4
};

class Input
{
public:
	CPPGAPI static bool IsKeyDown(Key key);
	CPPGAPI static bool IsKeyPressed(Key key);
	CPPGAPI static bool IsKeyReleased(Key key);

	CPPGAPI static bool IsMouseButtonDown(MouseButton button);
	CPPGAPI static bool IsMouseButtonPressed(MouseButton button);
	CPPGAPI static bool IsMouseButtonReleased(MouseButton button);

public:
	class Controller
	{
	public:
		CPPGAPI static bool IsControllerConnected(ControllerID controller = ControllerID::One);

		CPPGAPI static bool IsControllerButtonDown(ControllerButton button, ControllerID controller = ControllerID::One);
		CPPGAPI static bool IsControllerButtonPressed(ControllerButton button, ControllerID controller = ControllerID::One);
		CPPGAPI static bool IsControllerButtonReleased(ControllerButton button, ControllerID controller = ControllerID::One);

		CPPGAPI static float GetControllerAxis(ControllerAxis axis, ControllerID controller = ControllerID::One);
	
		CPPGAPI static void SetControllerMotor(ControllerMotor motor, float speed, ControllerID controller = ControllerID::One);

	public:
		static void Update();

	private:
		static bool connectedControllers[(int)ControllerID::Count];

		static XINPUT_STATE controllerStates[(int)ControllerID::Count];
		static XINPUT_STATE controllerStatesPrev[(int)ControllerID::Count];

		static bool controllerButtonStates[(int)ControllerButton::Count];
		static bool controllerButtonStatesPrev[(int)ControllerButton::Count];
	};

public:
	static void Update();

private:
	static bool keyStates[(int)Key::Count];
	static bool keyStatesPrev[(int)Key::Count];
};