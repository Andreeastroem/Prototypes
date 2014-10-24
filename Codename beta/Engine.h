//Engine.h

#pragma once

#include "DrawManager.h"
#include "TextureManager.h"

class SimpleReader;

class Engine
{
public:
	//Constructor
	Engine();

	//Essential functions
	bool Initialise();
	void Run();
	void Cleanup();

private:
	//Deltatime
	void UpdateDeltatime();
	sf::Clock m_clock;
	sf::Time m_previousTime;
	float m_deltatime;

	//Managers
	DrawManager* m_drawmanager;
	TextureManager* m_texturemanager;

	//Parsing
	SimpleReader* m_reader;

	//System
	System m_system;
};