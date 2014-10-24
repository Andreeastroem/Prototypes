//PerformanceGraph.cpp

#include "stdafx.h"

#include "PerformanceGraph.h"

PerformanceGraph::PerformanceGraph()
{
	m_origin = sf::Vector2f(0, 0);
	m_size = sf::Vector2f(50, 50);

	m_overlay = sf::RectangleShape(m_size);
	m_overlay.setPosition(m_origin);
	m_overlay.setFillColor(sf::Color(255, 255, 255, 80));

	m_maxfps = 150;
	m_maxSteps = 100;

	m_xDistance = m_size.x / m_maxSteps;
}

PerformanceGraph::PerformanceGraph(sf::Vector2f origin, sf::Vector2f size, const unsigned int &maxfps, const unsigned int &maxsteps)
{
	m_origin = origin;
	m_size = size;

	m_overlay = sf::RectangleShape(m_size);
	m_overlay.setPosition(m_origin);
	m_overlay.setFillColor(sf::Color(255, 255, 255, 80));

	m_maxfps = maxfps;
	m_maxSteps = maxsteps;

	m_xDistance = m_size.x / m_maxSteps;
}


void PerformanceGraph::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_overlay);

	states.transform *= getTransform();

	states.texture = NULL;

	target.draw(m_vertices, states);
}

void PerformanceGraph::Update(const float &deltatime)
{
	m_timeSinceLastDraw += deltatime;

	if (m_timeSinceLastDraw >= m_intervall)
	{
		int numberOfSteps = 1 / deltatime;
		float yPosition = (m_size.y / m_maxfps) * numberOfSteps;


		System::Debugger::FPS = numberOfSteps;

		if (m_vertices.getVertexCount() >= m_maxSteps)
		{
			for (int i = 0; i < m_vertices.getVertexCount(); i++)
			{
				m_vertices[i].position.x -= m_xDistance;
			}
			for (int i = 0; i < (m_vertices.getVertexCount() - 1); i++)
			{
				m_vertices[i] = m_vertices[i + 1];
			}

			m_vertices[m_vertices.getVertexCount() - 1].position = sf::Vector2f(m_origin.x + m_size.x, (m_origin.y + m_size.y) - yPosition);
		}
		else
		{
			for (int i = 0; i < m_vertices.getVertexCount(); i++)
			{
				m_vertices[i].position.x -= m_xDistance;
			}

			sf::Vector2f position(m_origin.x + m_size.x, (m_origin.y + m_size.y) - yPosition);

			sf::Vertex vertex = sf::Vertex(position);

			vertex.color = sf::Color::Cyan;

			m_vertices.append(vertex);
		}

		m_timeSinceLastDraw -= m_intervall;
	}
}

void PerformanceGraph::ClearGraph()
{
	m_vertices.clear();
}

void PerformanceGraph::SetOrigin(sf::Vector2f origin)
{
	m_origin = origin;
}

void PerformanceGraph::SetPrimitiveType(sf::PrimitiveType type)
{
	m_vertices.setPrimitiveType(type);
}