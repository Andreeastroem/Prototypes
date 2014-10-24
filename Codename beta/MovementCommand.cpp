//VerticalMovementCommand

#include "stdafx.h"

#include "GameObject.h"
#include "Input.h"

#include "MovementCommand.h"

MovementCommand::MovementCommand(int gamepadIndex)
{
	m_index = gamepadIndex;
}

void MovementCommand::Execute(GameObject& actor)
{
	m_force = sf::Vector2f(System::InputManager.m_Gamepad->GetJoystickValue(m_index, sf::Joystick::Axis::X),
		System::InputManager.m_Gamepad->GetJoystickValue(m_index, sf::Joystick::Axis::Y));
	actor.AddForce(m_force * System::DELTATIME);
}

void MovementCommand::Undo(GameObject& actor)
{
	actor.AddForce(-m_force);
}