//Debug.h

#pragma once

namespace Debug
{
	enum TextColour
	{
		BLUE = 1,
		GREEN,
		CYAN,
		RED,
		PURPLE,
		DARKYELLOW,
		DEFAULT,
		GREY,
		BRIGHTBLUE,
		BRIGHTGREEN,
		BRIGHTCYAN,
		BRIGHTRED,
		PINK,
		YELLOW,
		BRIGHTWHITE
	};

	void Log(const std::string &message);
	void Log(const char &c);
	void Log(const float &f);
	void Log(const int &i);
	void Log(const sf::Vector2f &point);
	void Log(const std::size_t &size);

	void LogError(const std::string &message);

	void SetColour(const int &value);
}