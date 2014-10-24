//Component.h

#pragma once

class GameObject;

class Component
{
public:
	//Constructor
	Component();

	//Deconstructor
	~Component();

	//Essential functions
	virtual void SetOwner(GameObject* Owner);

	virtual void Cleanup() = 0;
	virtual void Update() = 0;

	//Access functions


	//Public variables
	unsigned int ID;
	EComponentType type;
protected:
	GameObject* m_owner;
};