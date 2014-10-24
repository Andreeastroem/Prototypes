//System.cpp

#include "stdafx.h"

#include "Input.h"
#include "TextureManager.h"

#include "System.h"

float System::DELTATIME = 0.f;

unsigned int System::Window::HEIGHT = 0;
unsigned int System::Window::WIDTH = 0;

unsigned int System::Debugger::DRAWCALLS = 0;
unsigned int System::Debugger::FPS = 0;


sf::RenderWindow System::window;

Input System::InputManager;