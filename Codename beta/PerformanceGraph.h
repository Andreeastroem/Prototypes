//PerformanceGraph.h

#pragma once

class PerformanceGraph : public sf::Drawable, sf::Transformable
{
public:
	PerformanceGraph();
	PerformanceGraph(sf::Vector2f origin, sf::Vector2f size, const unsigned int &maxfps, const unsigned int &maxsteps);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void Update(const float &deltatime);
	void ClearGraph();

	void SetOrigin(sf::Vector2f origin);
	void SetPrimitiveType(sf::PrimitiveType type);

private:
	sf::VertexArray m_vertices;
	sf::Vector2f m_origin;
	sf::Vector2f m_size;

	sf::RectangleShape m_overlay;

	float m_timeSinceLastDraw = 0;
	float m_intervall = 0.1f;

	int m_maxfps;
	int m_maxSteps;

	float m_xDistance;
};