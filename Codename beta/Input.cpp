//Input.cpp

#include "stdafx.h"

#include "Input.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		m_CurrentKeyboardButtons[i] = false;
		m_PreviousKeyboardButtons[i] = false;
	}
}

Keyboard::~Keyboard()
{

}

bool Keyboard::KeyIsDown(int key) const
{
	return m_CurrentKeyboardButtons[key];
}

bool Keyboard::KeyIsDoneOnce(int key) const
{
	return m_CurrentKeyboardButtons[key] && !m_PreviousKeyboardButtons[key];
}

void Keyboard::PostUpdate()
{
	//Save the key inputs
	for (int i = 0; i < 256; i++)
	{
		m_PreviousKeyboardButtons[i] = m_CurrentKeyboardButtons[i];
	}
}

//End of Keyboard

//Mouse related

Mouse::Mouse()
{
	for (int i = 0; i < MOUSEBUTTONSIZE; i++)
	{
		m_CurrentMouseButtons[i] = false;
		m_PreviousMouseButtons[i] = false;
	}
}

Mouse::~Mouse()
{

}

bool Mouse::ButtonIsDown(MouseButton button)
{
	return m_CurrentMouseButtons[button];
}

bool Mouse::ButtonIsDownOnce(MouseButton button)
{
	return m_CurrentMouseButtons[button] && !m_PreviousMouseButtons[button];
}

void Mouse::PostUpdate()
{
	for (int i = 0; i < MOUSEBUTTONSIZE; i++)
	{
		m_PreviousMouseButtons[i] = m_CurrentMouseButtons[i];
	}
}

void Mouse::UpdatePosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2f Mouse::GetPosition()
{
	return m_position;
}

//End of mouse

//Gamepad

Gamepad::Gamepad()
{
	std::map<int, float> controller;

	for (int i = 0; i < 8; i++)
	{
		controller.insert(std::pair<int, float>(i, 0));
	}

	for (int i = 0; i < 4; i++)
	{
		m_Joysticks.push_back(controller);
	}

	sf::Joystick::update();

	for (int i = 3; i >= 0; i--)
	{
		if (sf::Joystick::isConnected(i))
		{
			m_JoysticksConnected = i + 1;
			break;
		}
	}
}

Gamepad::~Gamepad()
{

}

void Gamepad::PostUpdate()
{
	for (unsigned int i = 0; i < m_JoysticksConnected; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			m_PreviousGamepadButtons[i][j] = m_CurrentGamepadButtons[i][j];
		}
	}
}

float Gamepad::GetJoystickValue(int controller, int stick)
{
	if (m_JoysticksConnected > 0)
	{
		std::map<int, float>::iterator it = m_Joysticks[controller].find(stick);

		if (it != m_Joysticks[controller].end())
		{
			return it->second;
		}
	}


	return 0;
}

bool Gamepad::ButtonIsDown(int controller, int button)
{
	return m_CurrentGamepadButtons[controller][button];
}

bool Gamepad::ButtonIsDownOnce(int controller, int button)
{
	return m_CurrentGamepadButtons[controller][button] && !m_PreviousGamepadButtons[controller][button];
}

//End of gamepad

Input::Input()
{
	CloseWindow = false;
}

bool Input::ClosedWindow()
{
	return CloseWindow;
}

bool Input::Initialise()
{
	m_Mouse = new Mouse;
	if (m_Mouse == nullptr)
		return false;

	m_Keyboard = new Keyboard;
	if (m_Keyboard == nullptr)
		return false;

	m_Gamepad = new Gamepad;
	if (m_Gamepad == nullptr)
		return false;

	for (unsigned int i = 0; i < 5; i++)
	{
		m_gamepadStatus[i] = false;
	}

	m_usedGamepads = 0;

	return true;
}

void Input::Update(sf::Event &event)
{
	int KeyboardIndex = 0;
	int MouseIndex = 0;
	float x = 0;
	float y = 0;

	float joystickValue = 0;
	int joystickID = 0;
	int joystickAxis = 0;
	bool joystickMoved = false;

	switch (event.type)
	{
	case sf::Event::Closed:
		CloseWindow = true;
		break;

		//If there has been any actions on the keyboard
	case sf::Event::KeyPressed:
		//Escape key
		if (event.key.code == sf::Keyboard::Escape)
		{
			CloseWindow = true;
		}

		KeyboardIndex = event.key.code & 0xFF;
		m_Keyboard->m_CurrentKeyboardButtons[KeyboardIndex] = true;


		break;
		//If there has been any releases of keyboard inputs
	case sf::Event::KeyReleased:
		KeyboardIndex = event.key.code & 0xFF;
		m_Keyboard->m_CurrentKeyboardButtons[KeyboardIndex] = false;
		break;


		//Mouse events
	case sf::Event::MouseMoved:
		x = event.mouseMove.x;
		y = event.mouseMove.y;

		m_Mouse->UpdatePosition(sf::Vector2f(x, y));
		break;

	case sf::Event::MouseButtonPressed:
		MouseIndex = event.mouseButton.button & MOUSEBUTTONSIZE;
		m_Mouse->m_CurrentMouseButtons[MouseIndex] = true;
		break;

	case sf::Event::MouseButtonReleased:
		MouseIndex = event.mouseButton.button & MOUSEBUTTONSIZE;
		m_Mouse->m_CurrentMouseButtons[MouseIndex] = false;
		break;

		//Gamepad
	case sf::Event::JoystickConnected:
		m_Gamepad->m_JoysticksConnected = event.joystickConnect.joystickId + 1;
		m_gamepadStatus[event.joystickConnect.joystickId + 1] = true;
		break;
	case sf::Event::JoystickDisconnected:
		m_Gamepad->m_JoysticksConnected = event.joystickConnect.joystickId;
		m_gamepadStatus[event.joystickConnect.joystickId + 1] = false;
		break;

	case sf::Event::JoystickButtonPressed:
		m_Gamepad->m_CurrentGamepadButtons[event.joystickButton.joystickId][event.joystickButton.button] = true;
		break;
	case sf::Event::JoystickButtonReleased:
		m_Gamepad->m_CurrentGamepadButtons[event.joystickButton.joystickId][event.joystickButton.button] = false;
		break;

	case sf::Event::JoystickMoved:
		joystickID = event.joystickMove.joystickId;
		joystickAxis = event.joystickMove.axis;
		joystickValue = event.joystickMove.position;

		joystickMoved = true;
		break;

	default:
		break;
	}

	if (joystickMoved)
	{
		std::map<int, float>::iterator it = m_Gamepad->m_Joysticks[joystickID].find(joystickAxis);

		if (it != m_Gamepad->m_Joysticks[joystickID].end())
		{
			it->second = joystickValue;
		}

	}
}

void Input::PostUpdate()
{
	m_Mouse->PostUpdate();
	m_Keyboard->PostUpdate();
	m_Gamepad->PostUpdate();
}

void Input::Cleanup()
{
	if (m_Mouse != nullptr)
	{
		delete m_Mouse;
		m_Mouse = nullptr;
	}

	if (m_Keyboard != nullptr)
	{
		delete m_Keyboard;
		m_Keyboard = nullptr;
	}

	if (m_Gamepad != nullptr)
	{
		delete m_Gamepad;
		m_Gamepad = nullptr;
	}
}


unsigned int Input::ConnectedGamepads()
{
	return m_Gamepad->m_JoysticksConnected;
}