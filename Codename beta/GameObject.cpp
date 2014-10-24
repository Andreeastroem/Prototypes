//GameObject.cpp

#include "stdafx.h"

#include "Component.h"
#include "RenderingComponent.h"
#include "GamepadComponent.h"
#include "SpriteRenderer.h"
#include "PhysicsComponent2D.h"

#include "GameObject.h"

//Constructors
GameObject::GameObject()
{

}

//Essential functions
void GameObject::AddComponent(EComponentType T)
{
	Component* component;
	sf::Texture texture;
	//Add the given component
	switch (T)
	{
	case RENDERINGCOMPONENT:
		component = new RenderingComponent();
		component->SetOwner(this);
		m_Components.insert(std::pair<EComponentType, Component*>(T, component));
		break;
	case GAMEPADCOMPONENT:
		component = new GamepadComponent();
		component->SetOwner(this);
		m_Components.insert(std::pair<EComponentType, Component*>(T, component));
		break;
	case SPRITERENDERINGCOMPONENT:
		component = new SpriteRenderer(texture);
		component->SetOwner(this);
		m_Components.insert(std::pair<EComponentType, Component*>(T, component));
		break;
	case PHYSICSCOMPONENT2D:
		component = new PhysicsComponent2D();
		component->SetOwner(this);
		m_Components.insert(std::pair<EComponentType, Component*>(T, component));
		break;
	default:
		break;
	}
}

void GameObject::Update()
{
	std::map<EComponentType, Component*>::iterator it = m_Components.begin();
	
	while (it != m_Components.end())
	{
		it->second->Update();
		it++;
	}
}

void GameObject::AddForce(sf::Vector2f force)
{
	PhysicsComponent2D* pc = GetComponent<PhysicsComponent2D>(PHYSICSCOMPONENT2D);
	pc->AddForce(force);
	pc = nullptr;
}

void GameObject::OnCollision()
{

}

void GameObject::Cleanup()
{
	//Clear the components
	std::map<EComponentType, Component*>::iterator it = m_Components.begin();
	while (it != m_Components.end())
	{
		it->second->Cleanup();
		delete it->second;
		it->second = nullptr;
		it++;
	}
}

//Access functions
