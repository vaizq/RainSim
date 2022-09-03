#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Physics.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>
#include <chrono>
#include <random>

class Rain;

class RainDrop : public Physical
{
public:
	RainDrop(Rain& rain, Mesh& mesh, glm::vec3 pos);
	void onCollision(const glm::vec3& collisionPoint) override;
	void draw(const Shader& shader);
	// Modifiers
	void setScale(float scale);
	float getScale();
private:
	float m_scale;
	Mesh& m_mesh;
	Rain& m_rain;
};

class Rain
{
public:
	Rain(PhysicsSystem& physics, glm::vec3 center = glm::vec3(0.0f), float radius = 1.0f, float height = 1.0f);
	void splitDrop(RainDrop& drop);
	void update(double frameTime);
	void draw(const Shader& shader);
	// Modifiers
	void setIntensity(float value) { m_dropRate = value; }
	void setCenter(const glm::vec3& center);
	glm::vec3 getCenter() const;
	void setRadius(float r);
	float getRadius() const;
private:
	PhysicsSystem& m_physics;
	std::list<RainDrop> m_rainDrops;
	// position and dimensions
	glm::vec3 m_center;
	float m_radius;
	float m_height;
	Mesh m_rainDropMesh;
	// Drop generation stuff
	float m_dropRate = 0.3f; // Amount of waterdrops spawned per second per square
	std::chrono::steady_clock::time_point m_lastDropTime;
	std::mt19937 m_rng;
};




