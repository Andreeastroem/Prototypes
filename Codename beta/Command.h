//Command.h

#pragma once

class GameObject;

class Command
{
public:
	~Command()
	{
	};

	//Essential functions
	virtual void Execute(GameObject& actor) = 0;

	virtual void Undo(GameObject& actor) = 0;

private:

};
