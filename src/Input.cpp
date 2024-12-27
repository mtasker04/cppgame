#include <cppgame/Input.h>

#include <cppgame/Debug.h>

#include <Xinput.h>

bool Input::IsKeyDown(Key key) {
	if (key == Key::Count) return false;
	return m_KeyStates[(int)key];
}
bool Input::IsKeyPressed(Key key) {
	if (key == Key::Count) return false;
	return m_KeyStates[(int)key] && !m_KeyStatesPrev[(int)key];
}
bool Input::IsKeyReleased(Key key) {
	if (key == Key::Count) return false;
	return !m_KeyStates[(int)key] && m_KeyStatesPrev[(int)key];
}
bool Input::AnyKeyDown() {
	for (int i = 0; i < (int)Key::Count; i++) {
		if (m_KeyStates[m_Keys[i]]) return true;
	}
	return false;
}

bool Input::IsMouseButtonDown(MouseButton button) {
	if (button == MouseButton::Count) return false;
	return m_KeyStates[(int)button];
}
bool Input::IsMouseButtonPressed(MouseButton button) {
	if (button == MouseButton::Count) return false;
	return m_KeyStates[(int)button] && !m_KeyStatesPrev[(int)button];
}
bool Input::IsMouseButtonReleased(MouseButton button) {
	if (button == MouseButton::Count) return false;
	return !m_KeyStates[(int)button] && m_KeyStatesPrev[(int)button];
}
bool Input::AnyMouseButtonDown() {
	static int mbuttons[] = {
		(int)MouseButton::Left,
		(int)MouseButton::Right,
		(int)MouseButton::Middle,
		(int)MouseButton::XButton1,
		(int)MouseButton::XButton2
	};
	for (int i = 0; i < (int)MouseButton::Count; i++) {
		if (m_KeyStates[mbuttons[i]]) return true;
	}
	return false;
}

bool Input::AnyMouseOrKeyDown() {
	return AnyMouseButtonDown() || AnyKeyDown();
}

const InputMode& Input::GetInputMode() {
	return m_InputMode;
}

bool Input::Controller::IsControllerConnected(ControllerID controller) {
	if (controller == ControllerID::Count) return false;
	return m_ConnectedControllers[(int)controller];
}

bool Input::Controller::IsControllerButtonDown(ControllerButton button, ControllerID controller) {
	if (controller == ControllerID::Count || button == ControllerButton::Count) return false;
	return m_ControllerStates[(int)controller].Gamepad.wButtons & (int)button;
}
bool Input::Controller::IsControllerButtonPressed(ControllerButton button, ControllerID controller) {
	if (controller == ControllerID::Count || button == ControllerButton::Count) return false;
	return m_ControllerStates[(int)controller].Gamepad.wButtons & (int)button && !(m_ControllerStatesPrev[(int)controller].Gamepad.wButtons & (int)button);
}
bool Input::Controller::IsControllerButtonReleased(ControllerButton button, ControllerID controller) {
	if (controller == ControllerID::Count || button == ControllerButton::Count) return false;
	return !(m_ControllerStates[(int)controller].Gamepad.wButtons & (int)button) && m_ControllerStatesPrev[(int)controller].Gamepad.wButtons & (int)button;
}
bool Input::Controller::AnyControllerButtonDown(ControllerID controller) {
	if (controller == ControllerID::Count) return false;
	return m_ControllerStates[(int)controller].Gamepad.wButtons;
}

float Input::Controller::GetControllerAxis(ControllerAxis axis, float deadzoneMin, float deadzoneMax, ControllerID controller) {
	if (controller == ControllerID::Count || axis == ControllerAxis::Count) return 0.0f;
	Math::ClampRef(deadzoneMin, 0.0f, 1.0f);
	Math::ClampRef(deadzoneMax, 0.0f, 1.0f);
	if (deadzoneMin + deadzoneMax > 1.0f) {
		CGERR("Deadzone min and max combined must be less than or equal to 1.");
		return 0.0f;
	}
	bool isTrigger = (int)axis >= (int)ControllerAxis::TriggerLeft;
	short max = isTrigger ? 255 : 32767;
	short value = 0;
	switch (axis) {
	case ControllerAxis::JoystickLeftX:
		value = m_ControllerStates[(int)controller].Gamepad.sThumbLX;
		break;
	case ControllerAxis::JoystickLeftY:
		value = m_ControllerStates[(int)controller].Gamepad.sThumbLY;
		break;
	case ControllerAxis::JoystickRightX:
		value = m_ControllerStates[(int)controller].Gamepad.sThumbRX;
		break;
	case ControllerAxis::JoystickRightY:
		value = m_ControllerStates[(int)controller].Gamepad.sThumbRY;
		break;
	case ControllerAxis::TriggerLeft:
		value = m_ControllerStates[(int)controller].Gamepad.bLeftTrigger;
		break;
	case ControllerAxis::TriggerRight:
		value = m_ControllerStates[(int)controller].Gamepad.bRightTrigger;
		break;
	}
	float normalizedValue = (float)value / max;
	Math::AbsRef(normalizedValue);
	float sign = normalizedValue < 0 ? -1.0f : 1.0f;
	float range = deadzoneMax - deadzoneMin;
	if (!isTrigger) {
		if (normalizedValue < deadzoneMin) {
			return 0.0f;
		}
		else if (normalizedValue > deadzoneMax) {
			return Math::Clamp(normalizedValue * sign, -1.0f, 1.0f);
		}
		else {
			normalizedValue = (normalizedValue / range) - 1.0f - range;
			return Math::Clamp(normalizedValue * sign, -1.0f, 1.0f);
		}
	}
	else {
		if (normalizedValue < deadzoneMin) {
			return 0.0f;
		}
		else if (normalizedValue > deadzoneMax) {
			return Math::Clamp(normalizedValue, 0.0f, 1.0f);
		}
		else {
			normalizedValue = (normalizedValue / range) - 1.0f - range;
			return Math::Clamp(normalizedValue, 0.0f, 1.0f);
		}
	}
}
float Input::Controller::GetControllerAxisRaw(ControllerAxis axis, ControllerID controller) {
	if (controller == ControllerID::Count || axis == ControllerAxis::Count) return 0.0f;
	bool isTrigger = (int)axis >= (int)ControllerAxis::TriggerLeft;
	short max = isTrigger ? 255 : 32767;
	short value = 0;
	switch (axis) {
	case ControllerAxis::JoystickLeftX:
		value = m_ControllerStates[(int)controller].Gamepad.sThumbLX;
		break;
	case ControllerAxis::JoystickLeftY:
		value = m_ControllerStates[(int)controller].Gamepad.sThumbLY;
		break;
	case ControllerAxis::JoystickRightX:
		value = m_ControllerStates[(int)controller].Gamepad.sThumbRX;
		break;
	case ControllerAxis::JoystickRightY:
		value = m_ControllerStates[(int)controller].Gamepad.sThumbRY;
		break;
	case ControllerAxis::TriggerLeft:
		value = m_ControllerStates[(int)controller].Gamepad.bLeftTrigger;
		break;
	case ControllerAxis::TriggerRight:
		value = m_ControllerStates[(int)controller].Gamepad.bRightTrigger;
		break;
	}
	return Math::Clamp((float)value / max, -1.0f, 1.0f);
}

void Input::Controller::SetControllerMotor(ControllerMotor motor, float speed, ControllerID controller) {
	XINPUT_VIBRATION vibration = { 0 };
	if (motor == ControllerMotor::Left) {
		vibration.wLeftMotorSpeed = (WORD)(speed * 65535.0f);
	}
	else {
		vibration.wRightMotorSpeed = (WORD)(speed * 65535.0f);
	}
	XInputSetState((int)controller, &vibration);
}

void Input::Controller::Update() {
	for (int i = 0; i < (int)ControllerID::Count; i++) {
		m_ControllerStatesPrev[i] = m_ControllerStates[i];
	}
	for (int i = 0; i < (int)ControllerID::Count; i++) {
		ZeroMemory(&m_ControllerStates[i], sizeof(XINPUT_STATE));
		if (XInputGetState(i, &m_ControllerStates[i]) == ERROR_SUCCESS) {
			m_ConnectedControllers[i] = true;
		}
		else m_ConnectedControllers[i] = false;
	}
}

bool Input::Controller::m_ConnectedControllers[(int)ControllerID::Count];

XINPUT_STATE Input::Controller::m_ControllerStates[(int)ControllerID::Count];
XINPUT_STATE Input::Controller::m_ControllerStatesPrev[(int)ControllerID::Count];

bool Input::Controller::m_ControllerButtonStates[(int)ControllerButton::Count];
bool Input::Controller::m_ControllerButtonStatesPrev[(int)ControllerButton::Count];

void Input::Update() {
	for (int i = 0; i < (int)Key::Count; i++) {
		m_KeyStatesPrev[i] = m_KeyStates[i];
		m_KeyStates[i] = GetAsyncKeyState(m_Keys[i]) & 0x8000;
	}
	Controller::Update();
}

InputMode Input::m_InputMode = InputMode::KeyboardMouse;

bool Input::m_KeyStates[(int)Key::Count];
bool Input::m_KeyStatesPrev[(int)Key::Count];

int Input::m_Keys[(int)Key::Count] = {
	(int)Key::A,
	(int)Key::B,
	(int)Key::C,
	(int)Key::D,
	(int)Key::E,
	(int)Key::F,
	(int)Key::G,
	(int)Key::H,
	(int)Key::I,
	(int)Key::J,
	(int)Key::K,
	(int)Key::L,
	(int)Key::M,
	(int)Key::N,
	(int)Key::O,
	(int)Key::P,
	(int)Key::Q,
	(int)Key::R,
	(int)Key::S,
	(int)Key::T,
	(int)Key::U,
	(int)Key::V,
	(int)Key::W,
	(int)Key::X,
	(int)Key::Y,
	(int)Key::Z,
	(int)Key::Zero,
	(int)Key::One,
	(int)Key::Two,
	(int)Key::Three,
	(int)Key::Four,
	(int)Key::Five,
	(int)Key::Six,
	(int)Key::Seven,
	(int)Key::Eight,
	(int)Key::Nine,
	(int)Key::Escape,
	(int)Key::LControl,
	(int)Key::LShift,
	(int)Key::LAlt,
	(int)Key::LSystem,
	(int)Key::RControl,
	(int)Key::RShift,
	(int)Key::RAlt,
	(int)Key::RSystem,
	(int)Key::Menu,
	(int)Key::LBracket,
	(int)Key::RBracket,
	(int)Key::SemiColon,
	(int)Key::Comma,
	(int)Key::Period,
	(int)Key::Quote,
	(int)Key::Slash,
	(int)Key::BackSlash,
	(int)Key::Tilde,
	(int)Key::Equal,
	(int)Key::Dash,
	(int)Key::Space,
	(int)Key::Return,
	(int)Key::BackSpace,
	(int)Key::Tab,
	(int)Key::PageUp,
	(int)Key::PageDown,
	(int)Key::End,
	(int)Key::Home,
	(int)Key::Insert,
	(int)Key::Delete,
	(int)Key::Add,
	(int)Key::Subtract,
	(int)Key::Multiply,
	(int)Key::Divide,
	(int)Key::Left,
	(int)Key::Right,
	(int)Key::Up,
	(int)Key::Down,
	(int)Key::NumpadZero,
	(int)Key::NumpadOne,
	(int)Key::NumpadTwo,
	(int)Key::NumpadThree,
	(int)Key::NumpadFour,
	(int)Key::NumpadFive,
	(int)Key::NumpadSix,
	(int)Key::NumpadSeven,
	(int)Key::NumpadEight,
	(int)Key::NumpadNine,
	(int)Key::F1,
	(int)Key::F2,
	(int)Key::F3,
	(int)Key::F4,
	(int)Key::F5,
	(int)Key::F6,
	(int)Key::F7,
	(int)Key::F8,
	(int)Key::F9,
	(int)Key::F10,
	(int)Key::F11,
	(int)Key::F12,
	(int)Key::F13,
	(int)Key::F14,
	(int)Key::F15,
	(int)Key::Pause,
};