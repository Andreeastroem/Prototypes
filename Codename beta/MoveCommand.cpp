//MoveCommand.cpp

#include "stdafx.h"

#include "GameObject.h"

#include "MoveCommand.h"


//Constructors

MoveCommand::MoveCommand(sf::Vector2i target)
{
	m_TargetPosition.x = (float)target.x;
	m_TargetPosition.y = (float)target.y;
}

MoveCommand::~MoveCommand()
{
	if (m_Actor != nullptr)
		m_Actor = nullptr;
}

//Essential functions

void MoveCommand::Execute(GameObject& actor)
{
	m_Actor = &actor;
	m_LastPosition = actor.getPosition();
	actor.setPosition(m_TargetPosition);
}

void MoveCommand::Undo(GameObject& actor)
{
	m_Actor->setPosition(m_LastPosition);
}