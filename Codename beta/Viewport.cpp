//Viewport.cpp

#include "stdafx.h"

#include "Viewport.h"

//Constructors and deconstructor

Viewport::Viewport()
{

}

Viewport::Viewport(const sf::FloatRect &camera)
{
	m_View.setViewport(camera);
}

Viewport::Viewport(const sf::View &view)
{
	m_View = view;
}

Viewport::Viewport(const sf::Vector2f &position, const sf::Vector2f &size)
{
	sf::FloatRect view = sf::FloatRect(position.x, position.y, size.x, size.y);
	m_View.setViewport(view);
}

Viewport::Viewport(const float x, const float y, const unsigned int width, const unsigned int height)
{
	sf::FloatRect view = sf::FloatRect(x, y, width, height);
	m_View.setViewport(view);
}

Viewport::~Viewport()
{

}

//End of constructors and deconstructor