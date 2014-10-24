//GameObject.h

#pragma once

class Component;

class GameObject : public sf::Transformable
{
public:
	//Constructors
	GameObject();

	//Essential functions
	void AddComponent(EComponentType T);

	void Update();

	void Cleanup();

	void OnCollision();
	
	void AddForce(sf::Vector2f force);

	//Access functions
	template <class T>
	T* GetComponent(EComponentType t);

private:
	//components
	std::map<EComponentType, Component*> m_Components;

	//ID
	std::string m_id;
};

#include "GameObject.tpp"