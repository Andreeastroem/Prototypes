//DrawManager.h

#pragma once

#include "RenderingComponent.h"

#include "Profiler.h"

class DrawManager
{
public:
	DrawManager();

	void SetView(sf::RenderWindow &window, sf::View);

	//Generic draw function
	void Draw(sf::RenderWindow &window, sf::Drawable* object);

	void ClearScreen(sf::RenderWindow &window, int Red, int Green, int Blue, int Alpha);

	void DisplayScreen(sf::RenderWindow &window);
private:
};