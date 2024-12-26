#include <cppgame/Input.h>

#include <Xinput.h>

bool Input::IsKeyDown(Key key) {
	if (key == Key::Count) return false;
	return keyStates[(int)key];
}
bool Input::IsKeyPressed(Key key) {
	if (key == Key::Count) return false;
	return keyStates[(int)key] && !keyStatesPrev[(int)key];
}
bool Input::IsKeyReleased(Key key) {
	if (key == Key::Count) return false;
	return !keyStates[(int)key] && keyStatesPrev[(int)key];
}

bool Input::IsMouseButtonDown(MouseButton button) {
	if (button == MouseButton::Count) return false;
	return keyStates[(int)button];
}
bool Input::IsMouseButtonPressed(MouseButton button) {
	if (button == MouseButton::Count) return false;
	return keyStates[(int)button] && !keyStatesPrev[(int)button];
}
bool Input::IsMouseButtonReleased(MouseButton button) {
	if (button == MouseButton::Count) return false;
	return !keyStates[(int)button] && keyStatesPrev[(int)button];
}

bool Input::Controller::IsControllerConnected(ControllerID controller) {
	if (controller == ControllerID::Count) return false;
	return connectedControllers[(int)controller];
}

bool Input::Controller::IsControllerButtonDown(ControllerButton button, ControllerID controller) {
	if (controller == ControllerID::Count || button == ControllerButton::Count) return false;
	return controllerStates[(int)controller].Gamepad.wButtons & (int)button;
}
bool Input::Controller::IsControllerButtonPressed(ControllerButton button, ControllerID controller) {
	if (controller == ControllerID::Count || button == ControllerButton::Count) return false;
	return controllerStates[(int)controller].Gamepad.wButtons & (int)button && !(controllerStatesPrev[(int)controller].Gamepad.wButtons & (int)button);
}
bool Input::Controller::IsControllerButtonReleased(ControllerButton button, ControllerID controller) {
	if (controller == ControllerID::Count || button == ControllerButton::Count) return false;
	return !(controllerStates[(int)controller].Gamepad.wButtons & (int)button) && controllerStatesPrev[(int)controller].Gamepad.wButtons & (int)button;
}

float Input::Controller::GetControllerAxis(ControllerAxis axis, ControllerID controller) {
	if (controller == ControllerID::Count || axis == ControllerAxis::Count) return 0.0f;
	bool isTrigger = (int)axis >= (int)ControllerAxis::TriggerLeft;
	short max = isTrigger ? 255 : 32767;
	short value = 0;
	switch (axis) {
	case ControllerAxis::JoystickLeftX:
		value = controllerStates[(int)controller].Gamepad.sThumbLX;
		break;
	case ControllerAxis::JoystickLeftY:
		value = controllerStates[(int)controller].Gamepad.sThumbLY;
		break;
	case ControllerAxis::JoystickRightX:
		value = controllerStates[(int)controller].Gamepad.sThumbRX;
		break;
	case ControllerAxis::JoystickRightY:
		value = controllerStates[(int)controller].Gamepad.sThumbRY;
		break;
	case ControllerAxis::TriggerLeft:
		value = controllerStates[(int)controller].Gamepad.bLeftTrigger;
		break;
	case ControllerAxis::TriggerRight:
		value = controllerStates[(int)controller].Gamepad.bRightTrigger;
		break;
	}
	return Math::Clamp((float)value / (float)max, -1.0f, 1.0f);
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
		controllerStatesPrev[i] = controllerStates[i];
	}
	for (int i = 0; i < (int)ControllerID::Count; i++) {
		ZeroMemory(&controllerStates[i], sizeof(XINPUT_STATE));
		if (XInputGetState(i, &controllerStates[i]) == ERROR_SUCCESS) {
			connectedControllers[i] = true;
		}
		else connectedControllers[i] = false;
	}
}

bool Input::Controller::connectedControllers[(int)ControllerID::Count];

XINPUT_STATE Input::Controller::controllerStates[(int)ControllerID::Count];
XINPUT_STATE Input::Controller::controllerStatesPrev[(int)ControllerID::Count];

bool Input::Controller::controllerButtonStates[(int)ControllerButton::Count];
bool Input::Controller::controllerButtonStatesPrev[(int)ControllerButton::Count];

void Input::Update() {
	for (int i = 0; i < (int)Key::Count; i++) {
		keyStatesPrev[i] = keyStates[i];
		keyStates[i] = GetAsyncKeyState(i) & 0x8000;
	}
	Controller::Update();
}

bool Input::keyStates[(int)Key::Count];
bool Input::keyStatesPrev[(int)Key::Count];