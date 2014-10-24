//RenderingComponent.h

#pragma once

#include "Component.h"

class GameObject;

class RenderingComponent : public Component, public sf::Drawable, public sf::Transformable
{
public:
	//Constructors
	RenderingComponent();

	//Essential functions
	void Update();
	void Cleanup();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	//Access functions

protected:
	sf::VertexArray m_Vertices;

	sf::Texture m_Texture;
};