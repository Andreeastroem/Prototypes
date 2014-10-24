#include "stdafx.h"

#include "Debug.h"

#include <Windows.h>

//Print specified string
void Debug::Log(const std::string &message)
{
	std::cout << message << std::endl;
}

//Print specified character
void Debug::Log(const char &character)
{
	SetColour(Debug::BRIGHTBLUE);
	std::cout << character << std::endl;
	SetColour(Debug::DEFAULT);
}

//Print specified vector
void Debug::Log(const sf::Vector2f &vector)
{
	SetColour(Debug::BRIGHTCYAN);
	printf("Vector(%0.2f, %0.2f) \n", vector.x, vector.y);
	SetColour(Debug::DEFAULT);
}

//Print specified float
void Debug::Log(const float &f)
{
	SetColour(Debug::GREEN);
	printf("Float value: %0.2f \n", f);
	SetColour(Debug::DEFAULT);
}

//Print specified integer
void Debug::Log(const int &i)
{
	SetColour(Debug::GREEN);
	printf("Integer value: %i \n", i);
	SetColour(Debug::DEFAULT);
}

//Print specified size_t variable
void Debug::Log(const std::size_t &size)
{
	SetColour(Debug::GREEN);
	std::cout << "size_t value: " << size << std::endl;
	SetColour(Debug::DEFAULT);
}

//Print error message
void Debug::LogError(const std::string &message)
{
	SetColour(Debug::BRIGHTRED);
	Log(message);
	SetColour(Debug::DEFAULT);
}



/*
Change the command prompt colour
1. Blue
2. Green
3. Cyan
4. Red
5. Purple
6. Dark yellow
7. Default white
8. Grey
9. Bright blue
10. Bright green
11. Bright cyan
12. Bright red
13. Pink/Magenta
14. Yellow
15. Bright white
*/
void Debug::SetColour(const int &value)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}