//VerticalMovementCommand.h

#pragma once

#include "Command.h"

class MovementCommand : public Command
{
public:
	MovementCommand(int gamepadIndex);

	void Execute(GameObject& actor);
	void Undo(GameObject& actor);

private:
	int m_index;

	sf::Vector2f m_force;
};