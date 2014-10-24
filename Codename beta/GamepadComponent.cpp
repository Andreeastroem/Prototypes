//GamepadComponent.cpp

#include "stdafx.h"

#include "Command.h"
#include "GamepadComponent.h"
#include "Input.h"

GamepadComponent::GamepadComponent()
{
}

void GamepadComponent::Update()
{
	//If the gamepad index is 0 and the amount of controllers connected is greater than 0
	//set the controller index to that number
	if (m_gamepadIndex == 0 && System::InputManager.ConnectedGamepads() > System::InputManager.m_usedGamepads)
	{
		System::InputManager.m_usedGamepads++;
		m_gamepadIndex = System::InputManager.m_usedGamepads;

		System::InputManager.m_gamepadStatus[m_gamepadIndex] = true;
	}

	//If a gamepad has been disconnected and its id matches the internal id, disenable it to fetch information
	if (System::InputManager.m_gamepadStatus[m_gamepadIndex] && m_gamepadIndex > 0)
	{
		System::InputManager.m_usedGamepads--;
		m_gamepadIndex = 0;
	}

	//Check commands

	//buttons
	auto buttonIterator = m_command.begin();
	while (buttonIterator != m_command.end())
	{
		ExecuteButtonCommand(buttonIterator->second.first, buttonIterator->second.second);

		buttonIterator++;
	}

	//axis
	auto joystickIterator = m_joystickCommand.begin();
	while (joystickIterator != m_joystickCommand.end())
	{

		joystickIterator++;
	}
}

void GamepadComponent::Cleanup()
{

}

void GamepadComponent::AddCommandToAxis(const std::string name, sf::Joystick::Axis axis, Command* command)
{
	if (axis < sf::Joystick::AxisCount)
	{
		AxisPair pair;
		pair.a = axis;
		pair.b = axis;

		std::pair<AxisPair, Command*> id = std::pair<AxisPair, Command*>(pair, command);

		m_joystickCommand.insert(std::pair<std::string, std::pair<AxisPair, Command*>>(name, id));
	}
	else
	{
		Debug::LogError("Not a legit sf::Axis");
	}
}

void GamepadComponent::AddCommandToAxis(const std::string name, sf::Joystick::Axis axis, sf::Joystick::Axis axis2, Command* command)
{
	if (axis < sf::Joystick::AxisCount && axis2 < sf::Joystick::AxisCount)
	{
		AxisPair pair;
		pair.a = axis;
		pair.b = axis2;

		std::pair<AxisPair, Command*> id = std::pair<AxisPair, Command*>(pair, command);

		m_joystickCommand.insert(std::pair<std::string, std::pair<AxisPair, Command*>>(name, id));
	}
	else
	{
		Debug::LogError("Either axis one or axis two is not a legit sf::axis.");
	}
}

void GamepadComponent::AddCommandToButton(const std::string name, GamepadButton button, Command* command)
{
	if (button < GamepadButton::GAMEPADBUTTONSIZE)
	{
		GamepadCommand gc;
		gc.id = button;

		std::pair <GamepadButton, Command*> id = std::pair<GamepadButton, Command*>(button, command);

		m_command.insert(std::pair<std::string, std::pair<GamepadButton, Command*>>(name, id));
	}
}

bool GamepadComponent::ExecuteButtonCommand(const std::string &command)
{
	if (m_gamepadIndex != 0)
	{
		auto it = m_command.find(command);

		//Found the given command
		if (it != m_command.end())
		{
			//If the button is being pressed
			if (System::InputManager.m_Gamepad->ButtonIsDownOnce((m_gamepadIndex - 1), it->second.first))
				it->second.second->Execute(*m_owner);
		}
		return false;
	}
	else
	{
		Debug::LogError("No gamepad controller is connected to the device. \nPlease insert a controller to continue.");
		return false;
	}
}

bool GamepadComponent::CheckContinuedPressOnButton(const std::string &command)
{
	if (m_gamepadIndex != 0)
	{
		auto it = m_command.find(command);

		//Found the given command
		if (it != m_command.end())
		{
			//If the button is continously being pressed
			if (System::InputManager.m_Gamepad->ButtonIsDown((m_gamepadIndex - 1), it->second.first))
			{
				it->second.second->Execute(*m_owner);
				return true;
			}
		}
		return false;
	}
	else
	{
		Debug::LogError("No gamepad controller is connected to the device. \nPlease insert a controller to continue.");
		return false;
	}
}

bool GamepadComponent::ExecuteAxisCommand(const std::string &axisCommand)
{
	auto it = m_joystickCommand.find(axisCommand);

	//If the command has been set
	if (it != m_joystickCommand.end())
	{
		if (abs(System::InputManager.m_Gamepad->GetJoystickValue(m_gamepadIndex, it->second.first.a)) > 10 ||
			abs(System::InputManager.m_Gamepad->GetJoystickValue(m_gamepadIndex, it->second.first.b)) > 10)
		{
			it->second.second->Execute(*m_owner);
			return true;
		}
		return false;
	}
	else
	{
		Debug::LogError("No such command exists. Command name: " + axisCommand);
		return false;
	}
}

//Private functions

void GamepadComponent::ExecuteAxisCommand(sf::Joystick::Axis axis, Command* command)
{
	if (abs(System::InputManager.m_Gamepad->GetJoystickValue(m_gamepadIndex, axis)) > 10)
	{
		command->Execute(*m_owner);
	}
}

void GamepadComponent::ExecuteButtonCommand(GamepadButton button, Command* command)
{
	if (System::InputManager.m_Gamepad->ButtonIsDownOnce((m_gamepadIndex - 1), button))
		command->Execute(*m_owner);
}