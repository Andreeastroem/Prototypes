//A quick try on creating a profiler graph

#pragma once

#include "PerformanceGraph.h"

class Profiler : public sf::Drawable, public sf::Transformable
{
public:
	Profiler();
	Profiler(sf::Vector2f origin);
	Profiler(sf::Vector2f origin, sf::Vector2f size);
	Profiler(sf::Vector2f origin, sf::Vector2f size, int maxfps);
	Profiler(sf::Vector2f origin, sf::Vector2f size, int maxfps, int maxSteps);

	void Update(float deltatime);
	void Initialise(sf::Vector2f origin, sf::Vector2f size, int maxfps, int maxSteps);

	void SetOrigin(sf::Vector2f origin);
	void SetPrimitiveType(sf::PrimitiveType type);

	void SetDrawcalls(int &number);

	void Clear();

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void SetText();

	sf::RectangleShape m_overlay;

	PerformanceGraph m_graph;

	sf::VertexArray m_vertices;
	sf::Vector2f m_origin;
	sf::Vector2f m_size;

	sf::Text m_fps;
	sf::Text m_drawcalls;
	sf::Font m_font;
};