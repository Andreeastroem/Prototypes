//Engine.cpp

#pragma once

#include "stdafx.h"

#include "GameObject.h"
#include "MoveCommand.h"
#include "SimpleReader.h"
#include "Profiler.h"
#include "Input.h"

//Commands
#include "MovementCommand.h"

//Components
#include "RenderingComponent.h"
#include "GamepadComponent.h"
#include "SpriteRenderer.h"
#include "PhysicsComponent2D.h"

//End of components

#include "Engine.h"

//Constructor

Engine::Engine()
{

}

//End of constructors

//Essential functions

bool Engine::Initialise()
{
	m_system.window.create(sf::VideoMode(1280, 720), "Early access", sf::Style::Default);

	m_system.window.setFramerateLimit(60);

	System::Window::HEIGHT = 720;
	System::Window::WIDTH = 1280;

	if (!System::InputManager.Initialise())
		return false;

	m_texturemanager = new TextureManager;
	if (!m_texturemanager->Initialise("../data/textures/", "png"))
		return false;

	m_reader = new SimpleReader;

	m_reader->Initialise("../data/");
	m_reader->ReadFile("ParsingTest.txt");

	m_drawmanager = new DrawManager;

	return true;
}

void Engine::Run()
{
	Profiler profiler = Profiler(sf::Vector2f(System::Window::WIDTH * 0.01f, System::Window::HEIGHT * 0.8f), 
		sf::Vector2f(System::Window::WIDTH * 0.2f, System::Window::HEIGHT * 0.1f), 150, 100);
	profiler.SetPrimitiveType(sf::PrimitiveType::LinesStrip);

	GameObject actor;
	actor.AddComponent(RENDERINGCOMPONENT);
	actor.AddComponent(GAMEPADCOMPONENT);
	actor.AddComponent(PHYSICSCOMPONENT2D);

	/*
	SpriteRenderer* sr = actor.GetComponent<SpriteRenderer>(SPRITERENDERINGCOMPONENT);
	sr->setTexture(*m_texturemanager->GetTexture("chara1b"));
	sr->setSize(sf::Vector2f(128, 128));
	*/

	GamepadComponent* gc = actor.GetComponent<GamepadComponent>(GAMEPADCOMPONENT);

	MovementCommand vmc = MovementCommand(System::InputManager.m_usedGamepads);

	gc->AddCommandToAxis("move", sf::Joystick::Axis::X, sf::Joystick::Axis::Y, &vmc);

	
	//sr = nullptr;

	m_clock.restart();

	while (m_system.window.isOpen())
	{
		sf::Event event;
		//check events
		while (m_system.window.pollEvent(event))
		{
			System::InputManager.Update(event);

			if (System::InputManager.ClosedWindow())
				System::window.close();

		}	//End of events

		UpdateDeltatime();

		m_drawmanager->ClearScreen(System::window, 0, 0, 0, 255);

		RenderingComponent* rc = actor.GetComponent<RenderingComponent>(RENDERINGCOMPONENT);

		if (rc != nullptr)
		{
			m_drawmanager->Draw(System::window, rc);
		}

		rc = nullptr;
		
		gc->ExecuteAxisCommand("move");

		actor.Update();
		profiler.Update(m_deltatime);

		m_drawmanager->Draw(System::window, &profiler);

		m_drawmanager->DisplayScreen(System::window);
		
	}

	gc = nullptr;
}

void Engine::Cleanup()
{
	if (m_reader != nullptr)
	{
		delete m_reader;
		m_reader = nullptr;
	}

	if (m_drawmanager != nullptr)
	{
		delete m_drawmanager;
		m_drawmanager = nullptr;
	}

	if (m_texturemanager != nullptr)
	{
		m_texturemanager->Cleanup();
		delete m_texturemanager;
		m_texturemanager = nullptr;
	}

	System::InputManager.Cleanup();
}

void Engine::UpdateDeltatime()
{
	//Create a temporary time variable
	sf::Time tempTime = m_clock.getElapsedTime();

	//set the deltatime
	m_deltatime = tempTime.asSeconds() - m_previousTime.asSeconds();

	m_system.DELTATIME = m_deltatime;

	//Change the previous time variable
	m_previousTime = tempTime;
}

//End of essential functions

//Access functions

//End of access functions