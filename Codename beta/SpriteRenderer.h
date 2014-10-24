//SpriteRenderer.h


#pragma once

#include "Component.h"

class SpriteRenderer : public Component, public sf::Drawable, public sf::Transformable
{
public:
	SpriteRenderer(sf::Texture texture);

	void Cleanup();
	void Update();

	void setTexture(sf::Texture texture);
	void setSize(sf::Vector2f size);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	sf::Vector2f m_size;
	sf::VertexArray m_vertices;
	sf::Texture m_texture;
};