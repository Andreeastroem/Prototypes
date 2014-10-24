//A first try on making a profiling graph

#include "stdafx.h"

#include "Profiler.h"

//Constructors

Profiler::Profiler()
{
	Initialise(sf::Vector2f(), sf::Vector2f(150, 150), 150, 30);
}

Profiler::Profiler(sf::Vector2f origin)
{
	Initialise(origin, sf::Vector2f(50, 50), 150, 30);
}

Profiler::Profiler(sf::Vector2f origin, sf::Vector2f size)
{
	Initialise(origin, size, 150, 30);
}

Profiler::Profiler(sf::Vector2f origin, sf::Vector2f size, int maxfps)
{
	Initialise(origin, size, maxfps, 30);
}

Profiler::Profiler(sf::Vector2f origin, sf::Vector2f size, int maxfps, int maxSteps)
{
	Initialise(origin, size, maxfps, maxSteps);
}

//End of constructors

//Essential functions

void Profiler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_overlay);
	target.draw(m_graph);
	target.draw(m_fps);
	target.draw(m_drawcalls);

	//update any potential positions
	states.transform *= getTransform();

	states.texture = NULL;

	target.draw(m_vertices, states);
}

void Profiler::Update(float deltatime)
{
	m_graph.Update(deltatime);

	//Try to make this a little bit easier to access 
	m_fps.setString("FPS: " + std::to_string(System::Debugger::FPS));
	m_drawcalls.setString("Drawcalls: " + std::to_string(System::Debugger::DRAWCALLS));
}

void Profiler::Initialise(sf::Vector2f origin, sf::Vector2f size, int maxfps, int maxSteps)
{
	m_graph = PerformanceGraph(origin, size, maxfps, maxSteps);

	m_overlay = sf::RectangleShape(sf::Vector2f(1280, 720));
	m_overlay.setPosition(sf::Vector2f(0, 0));
	m_overlay.setFillColor(sf::Color(0, 0, 0, 180));

	SetText();
}

void Profiler::Clear()
{
	m_graph.ClearGraph();
}

void Profiler::SetOrigin(sf::Vector2f origin)
{
	m_graph.SetOrigin(origin);
}

void Profiler::SetPrimitiveType(sf::PrimitiveType type)
{
	m_graph.SetPrimitiveType(type);
}

void Profiler::SetText()
{
	//font and text
	if (!m_font.loadFromFile("../data/fonts/Rudelsberg.ttf"))
	{
		//error loading font
		Debug::Log("Problems occured while trying to load font from: ../data/fonts/Sans Plate Caps.ttf");
	}
	//Drawcalls position 0, 0
	m_drawcalls.setFont(m_font);

	//Fps position 0, 0 + character size
	m_fps.setPosition(0, m_drawcalls.getCharacterSize());
	m_fps.setFont(m_font);
	m_fps.setString("0");
	m_fps.setCharacterSize(24);
	m_fps.setColor(sf::Color::White);
	m_fps.setStyle(sf::Text::Bold);
	

	
}

void Profiler::SetDrawcalls(int &number)
{
	m_drawcalls.setString("Drawcalls: " + std::to_string(number + 3));
}