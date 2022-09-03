#include "Physics.h"
#include <iostream>

void PhysicsSystem::update(float frameTime)
{
	// Update objects 
	for (Physical* object : m_objects)
	{
		// Move object
		object->m_pos += object->m_velo * frameTime;
		// Apply gravity
		object->m_velo += m_gravity * frameTime;
	}

	// Check collisions between object and ground (y=0)
	for (Physical* object : m_objects)
	{
		const glm::vec3 bottom(object->m_pos.x, object->m_pos.y - object->m_radius, object->m_pos.z);
		if (bottom.y <= 0.0f)
		{
			object->m_pos.y = 0.0f + object->m_radius;
			object->onCollision(bottom);
		}
	}

	// Collision between objects
/*
	// Check collisions between object
	for (Physical* object : m_objects)
	{
		for (Physical* other : m_objects) {
			if (object == other)
				continue;



			glm::vec3 diff = other->m_pos - object->m_pos;
			if (diff.length() < object->m_radius + other->m_radius)
			{
				// Objects collide
				glm::vec3 collisionPoint = object->m_pos + object->m_radius * glm::normalize(diff); // Simple and beautiful
				object->onCollision(collisionPoint);
				other->onCollision(collisionPoint);
			}
		}
	}
	*/
}


void PhysicsSystem::addObject(Physical* object)
{
//	m_objectQueue.push(object);
	m_objects.push_back(object);
}

void PhysicsSystem::removeObject(Physical* object)
{
	m_objects.remove(object);
}

void PhysicsSystem::setGravity(const glm::vec3& g)
{
	m_gravity = g;
}

