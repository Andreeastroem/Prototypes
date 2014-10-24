//Physicscomponent for 2D objects, handles force and friction

#pragma once

#include "Component.h"

class GameObject;

class PhysicsComponent2D : public Component
{
public:
	PhysicsComponent2D();
	PhysicsComponent2D(float mass);

	//Inherited functions
	void Update();
	void Cleanup();

	//essential functions
	void AddForce(sf::Vector2f force);

	//access functions
	void SetMoveable(bool state);
	bool GetMoveable();
	
	void SetVelocity(sf::Vector2f velocity);				//Not adviced to use this function as it gives hacky motion
	sf::Vector2f GetVelocity();

	float GetMagnitude();

	float GetMass();
	void SetMass(float mass);

	sf::Vector2f GetAcceleration();
	void SetAcceleration(sf::Vector2f acceleration);	//Not adviced to use this function as it gives hacky motion

	float GetForce();
private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float m_MaxMagnitude;
	float m_mass;

	bool m_isMoveable;
};