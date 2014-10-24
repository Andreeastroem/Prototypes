//GamepadComponent

#include "Component.h"

class Command;

class GamepadComponent : public Component
{
	struct GamepadCommand
	{
		unsigned int id;
	};
	struct AxisPair
	{
		sf::Joystick::Axis a;
		sf::Joystick::Axis b;
	};
public:
	GamepadComponent();

	void Update();
	void Cleanup();

	void AddCommandToAxis(const std::string name, sf::Joystick::Axis axis, Command* command);
	void AddCommandToAxis(const std::string name, sf::Joystick::Axis axis, sf::Joystick::Axis axis2, Command* command);
	void AddCommandToButton(const std::string name, GamepadButton button, Command* command);
	bool ExecuteButtonCommand(const std::string &name);
	bool ExecuteAxisCommand(const std::string &axisCommand);
	bool CheckContinuedPressOnButton(const std::string &name);
private:
	std::map<std::string, std::pair<GamepadButton, Command*>> m_command;
	std::map<std::string, std::pair<AxisPair, Command*>> m_joystickCommand;

	void ExecuteButtonCommand(GamepadButton button, Command* command);
	void ExecuteAxisCommand(sf::Joystick::Axis axis, Command* command);

	unsigned int m_gamepadIndex;
};