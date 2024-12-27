#pragma once

#include <cppgame/Debug.h>
#include <cppgame/Input.h>
#include <cppgame/scripting/Behaviour.h>

class TestScript : public Behaviour
{
public:
	TestScript(GameObject& gObject) : Behaviour(gObject) {}

	void Start() override {
		Debug::Log("TestScript started.");
	}

	void Update() override {
		// Check if controller is connected
		if (Input::Controller::IsControllerConnected()) {
			// Print controller info
			if (Input::Controller::IsControllerButtonDown(ControllerButton::X)) {
				Debug::Log("X button is down.");
			}
			float leftJoystickXAxis = Input::Controller::GetControllerAxis(ControllerAxis::JoystickLeftX, 0.1f, 0.9f);
			printf("Left joystick X axis: %f", leftJoystickXAxis);
		}
		else {
			Debug::Warn("No controller is connected.");
		}
	}

private:
	InputMode inputMode = InputMode::KeyboardMouse;
};