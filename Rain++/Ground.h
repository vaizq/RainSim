#pragma once
#include "Mesh.h"
#include "Physics.h"
#include <glm/glm.hpp>


class Ground
{
public:
	Ground();
	void draw(const Shader& shader);
private:
	Mesh m_mesh;
};

