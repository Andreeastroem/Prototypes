//System.h

//A class to hold certain variables that can be needed from wherever in the code.

#pragma once

class Input;

class System
{
public:
	struct Window
	{
		static unsigned int WIDTH;
		static unsigned int HEIGHT;
	};

	struct Debugger
	{
		static unsigned int DRAWCALLS;
		static unsigned int FPS;
	};

	static float DELTATIME;

	static sf::RenderWindow window;
	
	static Input InputManager;

private:
	
};