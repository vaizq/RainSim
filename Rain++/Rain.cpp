#include "Rain.h"
#include "vertexData.h"
#include <math.h>
#include <GLFW/glfw3.h>

constexpr float PI = 3.14159265f;

RainDrop::RainDrop(Rain& rain, Mesh& mesh, glm::vec3 pos)
	: m_rain(rain), m_mesh(mesh), Physical(pos, glm::vec3(0), 1.0f)
{
	setScale(0.1f);
}

void RainDrop::onCollision(const glm::vec3& collisionPoint)
{
	m_velo = -m_velo * 0.2f;
	m_rain.splitDrop(*this);
}

void RainDrop::draw(const Shader& shader)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, m_pos);
	model = glm::scale(model, glm::vec3(m_scale, m_scale, m_scale));
	glm::vec4 color(0.0f, 0.0f, 0.8f, 1.0f);
	shader.setMat4("model", model);
	shader.setVec4("color", color);
	m_mesh.draw(shader);
}

void RainDrop::setScale(float scale)
{
	m_scale = scale;
	m_radius = scale;
}

float RainDrop::getScale()
{
	return m_scale;
}


Rain::Rain(PhysicsSystem& physics, glm::vec3 center, float radius, float height)
	: m_physics(physics), m_center(center), m_radius(radius), m_height(height), m_rainDropMesh(vgen::createPyramid(0.3f, 1.0f))
{
	std::random_device rd;
	m_rng.seed(rd());
}

void Rain::splitDrop(RainDrop& drop)
{
	constexpr std::size_t maxN = 4;
	std::uniform_int_distribution<std::size_t> nDist(0, maxN);
	const std::size_t n = nDist(m_rng);

	std::uniform_real_distribution<float> dirDist(-1.0f, 1.0f);
	std::uniform_real_distribution<float> sizeDist(0.0f, 1.0f);

	float totalSize = drop.getScale();

	// Split drop to n drops
	for (std::size_t i = 0; i < n; i++)
	{
		glm::vec3 velo(dirDist(m_rng), abs(dirDist(m_rng)), dirDist(m_rng));
		velo = glm::normalize(velo) * glm::length(drop.m_velo);

		RainDrop newDrop(*this, m_rainDropMesh, drop.m_pos + 0.01f);
		newDrop.m_velo = velo;
		newDrop.setScale(drop.getScale() / n);
//		newDrop.m_radius = drop.m_radius / n;
		m_rainDrops.push_back(newDrop);
		m_physics.addObject(&m_rainDrops.back());
	}
	
	drop.setScale(0.0f);
}

void Rain::update(double frameTime)
{
	using namespace std::chrono;
	// Create now rain drops
	const float dropsPerSec = m_dropRate * PI * powf(m_radius, 2); // How many drops must be generated / sec
	const float dropInterval = 1.0f / dropsPerSec; // How often new drops must be generated

	static double lastUpdate = -1.0;

	double timeNow = glfwGetTime();
	if (lastUpdate < 0.0)
		lastUpdate = timeNow;

	const std::size_t newDropCount = (timeNow - lastUpdate) / dropInterval;
	if (newDropCount > 0)
		lastUpdate = timeNow;

	for (std::size_t i = 0; i < newDropCount; i++)
	{
		// Calculate random position for a new rain drop
		std::uniform_real_distribution<float> angleDist(0.0, 2 * PI);
		float angle = angleDist(m_rng);
		std::uniform_real_distribution<float> distanceDist(0.0, m_radius);
		float distance = distanceDist(m_rng);
		glm::vec3 pos(m_center.x + distance * sin(angle), m_center.y + m_height, m_center.z + distance * cos(angle));

		// Add new raindrop
		m_rainDrops.push_back(RainDrop(*this, m_rainDropMesh, pos));
		m_physics.addObject(&m_rainDrops.back());
	}

	constexpr float minScale = 0.02f;
	// Remove 'dead' rain drops
	for (auto it = m_rainDrops.begin(); it != m_rainDrops.end();)
	{
		if (it->getScale() < minScale)
		{
			m_physics.removeObject(&(*it));
			it = m_rainDrops.erase(it);
		}
		else {
			++it;
		}
	}
}

void Rain::draw(const Shader& shader)
{
	for (auto& drop : m_rainDrops)
	{
		drop.draw(shader);
	}
}

void Rain::setCenter(const glm::vec3& center)
{
	m_center = center;
}

glm::vec3 Rain::getCenter() const
{
	return m_center;
}

void Rain::setRadius(float r)
{
	m_radius = r;
}

float Rain::getRadius() const
{
	return m_radius;
}
