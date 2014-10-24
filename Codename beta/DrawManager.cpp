//DrawManager.cpp

#include "stdafx.h"

#include "DrawManager.h"

DrawManager::DrawManager()
{
}

void DrawManager::SetView(sf::RenderWindow &window, sf::View view)
{
	window.setView(view);
}

void DrawManager::Draw(sf::RenderWindow &window, sf::Drawable* object)
{
	System::Debugger::DRAWCALLS++;
	window.draw(*object);
}

void DrawManager::ClearScreen(sf::RenderWindow &window, int Red, int Green, int Blue, int Alpha)
{
	window.clear(sf::Color(Red, Green, Blue, Alpha));

	System::Debugger::DRAWCALLS = 0;
}

void DrawManager::DisplayScreen(sf::RenderWindow &window)
{
	window.display();
}