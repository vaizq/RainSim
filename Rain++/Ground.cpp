#include "Ground.h"
#include "vertexData.h"

Ground::Ground()
	: m_mesh(vgen::createPlane())
{
}


void Ground::draw(const Shader& shader)
{
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(10.0f, 0.0f, 10.0f));
	glm::vec4 color(0.2f, 0.2f, 0.2f, 1.0f);
	shader.setMat4("model", model);
	shader.setVec4("color", color);
	m_mesh.draw(shader);
}
