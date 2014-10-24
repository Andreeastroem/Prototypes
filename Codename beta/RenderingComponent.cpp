//RenderingComponent.cpp

#include "stdafx.h"

#include "GameObject.h"

#include "RenderingComponent.h"

//Constructor
RenderingComponent::RenderingComponent()
{
	sf::Vertex vertex = sf::Vertex(sf::Vector2f(), sf::Color(255, 200, 120, 255));
	m_Vertices.append(vertex);
	vertex = sf::Vertex(sf::Vector2f(0, 40), sf::Color(200, 100, 220, 255));
	m_Vertices.append(vertex);
	vertex = sf::Vertex(sf::Vector2f(40, 0), sf::Color(140, 180, 20, 255));
	m_Vertices.append(vertex);
	vertex = sf::Vertex(sf::Vector2f(40, 40), sf::Color(140, 180, 20, 255));
	m_Vertices.append(vertex);

	m_Vertices.setPrimitiveType(sf::PrimitiveType::Quads);

	type = RENDERINGCOMPONENT;
}

//Essential functions
void RenderingComponent::Update()
{
	//Update the visuals
	setPosition(m_owner->getPosition());

	//Draw the visuals

}

void RenderingComponent::Cleanup()
{
	Component::Cleanup();
}

void RenderingComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	states.transform *= getTransform();

	states.texture = &m_Texture;

	target.draw(m_Vertices, states);
}

//Access functions
