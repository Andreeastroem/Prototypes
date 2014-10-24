//Component.cpp

#include "stdafx.h"

#include "GameObject.h"

#include "Component.h"

//Constructor
Component::Component()
{

}

//Deconstructor
Component::~Component()
{

}

//Essential functions
void Component::SetOwner(GameObject* owner)
{
	m_owner = owner;
}

void Component::Cleanup()
{
	if (m_owner != nullptr)
	{
		m_owner = nullptr;
	}
}

void Component::Update()
{

}

//Access functions