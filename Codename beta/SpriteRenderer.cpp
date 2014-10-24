//SpriteRenderer.cpp

#include "stdafx.h"

#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(sf::Texture texture)
{
	m_texture = texture;
	sf::Vertex vertex = sf::Vertex();
	m_vertices.append(vertex);
	m_vertices.append(vertex);
	m_vertices.append(vertex);
	m_vertices.append(vertex);
}

void SpriteRenderer::Update()
{

}

void SpriteRenderer::Cleanup()
{
	Component::Cleanup();
}

void SpriteRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &m_texture;

	target.draw(m_vertices, states);
}

void SpriteRenderer::setTexture(sf::Texture texture)
{
	m_texture = texture;
}

void SpriteRenderer::setSize(sf::Vector2f size)
{
	m_size = size;

	m_vertices[0].position = getPosition();
	m_vertices[1].position = sf::Vector2f(m_vertices[0].position.x + m_size.x, m_vertices[0].position.y);
	m_vertices[2].position = sf::Vector2f(m_vertices[0].position.x, m_vertices[0].position.y + m_size.y);
	m_vertices[3].position = sf::Vector2f(m_vertices[1].position.x, m_vertices[2].position.y);
}