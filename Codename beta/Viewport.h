//Viewport.h
//A class for creating new regions on the screen.

#pragma once

class Viewport
{
public:
	Viewport();
	Viewport(const sf::FloatRect &camera);
	Viewport(const sf::View &view);
	Viewport(const sf::Vector2f &position, const sf::Vector2f &size);
	Viewport(const float x, const float y, const unsigned int width, const unsigned int height);
	~Viewport();

	sf::View m_View;
};