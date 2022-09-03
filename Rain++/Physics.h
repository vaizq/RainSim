#pragma once
#include <glm/glm.hpp>
#include <list>
#include <queue>


struct Physical
{
	Physical(glm::vec3 pos, glm::vec3 velo, float radius)
		: m_pos(pos), m_velo(velo), m_radius(radius)
	{}
	virtual ~Physical() {}

	virtual void onCollision(const glm::vec3& collisionPoint) = 0;

	glm::vec3 m_pos;
	glm::vec3 m_velo;
	float m_radius; // For simplest 3d collision detection
};

class PhysicsSystem
{
public:
	static PhysicsSystem& instance() {
		static PhysicsSystem instance;
		return instance;
	}
	void update(float frameTime);
	void addObject(Physical* object);
	void removeObject(Physical* object);
	// Modifiers
	void setGravity(const glm::vec3& g);
private:
	PhysicsSystem() {}
	std::list<Physical*> m_objects;
	glm::vec3 m_gravity = glm::vec3(0, -5, 0);
};


