//A component for handling simple physics in 2D

#include "stdafx.h"

//Forward declarations
#include "GameObject.h"

#include "PhysicsComponent2D.h"

PhysicsComponent2D::PhysicsComponent2D()
{
	m_isMoveable = false;
	m_mass = 1;
}

//Inherited members
void PhysicsComponent2D::Update()
{
	m_velocity += m_acceleration;
	m_owner->move(m_velocity);

	m_velocity *= 0.05f;
}
void PhysicsComponent2D::Cleanup()
{
	Component::Cleanup();
}

//Essential functions
void PhysicsComponent2D::AddForce(sf::Vector2f force)
{

	m_acceleration += force * m_mass;
}

//Access functions
void PhysicsComponent2D::SetMoveable(bool state)
{
	m_isMoveable = state;
}
bool PhysicsComponent2D::GetMoveable()
{
	return m_isMoveable;
}
void PhysicsComponent2D::SetVelocity(sf::Vector2f velocity)
{
	m_velocity = velocity;
}
sf::Vector2f PhysicsComponent2D::GetVelocity()
{
	return m_velocity;
}
float PhysicsComponent2D::GetMagnitude()
{
	return sqrtf(powf(m_velocity.x, 2) + powf(m_velocity.y, 2));
}
float PhysicsComponent2D::GetMass()
{
	return m_mass;
}
void PhysicsComponent2D::SetMass(float mass)
{
	m_mass = mass;
}
sf::Vector2f PhysicsComponent2D::GetAcceleration()
{
	return m_acceleration;
}
void PhysicsComponent2D::SetAcceleration(sf::Vector2f acceleration)
{
	m_acceleration = acceleration;
}
float PhysicsComponent2D::GetForce()
{
	return sqrtf(powf(m_mass * m_acceleration.x, 2) +
		powf(m_mass * m_acceleration.y, 2));
}