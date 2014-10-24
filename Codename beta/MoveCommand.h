//MoveCommand.h

#pragma once

#include "Command.h"

class MoveCommand : public Command
{
public:
	//Constructors
	MoveCommand(sf::Vector2i target);

	~MoveCommand();

	//Essential functions
	void Execute(GameObject& actor);
	void Undo(GameObject& actor);

private:
	sf::Vector2f m_TargetPosition;
	sf::Vector2f m_LastPosition;

	//Pointer to the optional object
	GameObject* m_Actor;
};