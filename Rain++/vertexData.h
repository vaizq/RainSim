#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include "Mesh.h"
#include <vector>


namespace vgen
{
	static std::vector<Vertex> createPlane() {
		const glm::vec3 normal(0, 1, 0);
		std::vector<Vertex> plane =
		{
			Vertex(glm::vec3(1, 0, 1), normal, glm::vec3(1, 0, 1)),
			Vertex(glm::vec3(1, 0, -1), normal, glm::vec3(1, 0, -1)),
			Vertex(glm::vec3(-1, 0, 1), normal, glm::vec3(-1, 0, 1)),

			Vertex(glm::vec3(-1, 0, 1), normal, glm::vec3(-1, 0, 1)),
			Vertex(glm::vec3(1, 0, -1), normal, glm::vec3(1, 0, -1)),
			Vertex(glm::vec3(-1, 0, -1), normal, glm::vec3(-1, 0, -1)),
		};
		return plane;
	}

	static std::vector<Vertex> createTriangle() {
		const glm::vec3 normal(0, 0, 1);
		std::vector<Vertex> triangle =
		{
			Vertex(glm::vec3(0, 1, 0), normal, glm::vec3(0.5, 1, 0)),
			Vertex(glm::vec3(1, -1, 0), normal, glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(-1, -1, 0), normal, glm::vec3(-1, 0, 0)),
		};
		return triangle;
	}

	static std::vector<Vertex> createPyramid(float w, float h) {

		const glm::vec3 normal(0, 0, 0);


		std::vector<Vertex> pyramid =
		{
			// Front face
			Vertex(glm::vec3(0, h/2, 0), normal, glm::vec3(0.5, 1, 0)),
			Vertex(glm::vec3(-w/2, -h/2, w/2), normal, glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(w/2, -h/2, w/2), normal, glm::vec3(-1, 0, 0)),

			// Right face
			Vertex(glm::vec3(0, h/2, 0), normal, glm::vec3(0.5, 1, 0)),
			Vertex(glm::vec3(w/2, -h/2, w/2), normal, glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(w/2, -h/2, -w/2), normal, glm::vec3(-1, 0, 0)),

			// Back face
			Vertex(glm::vec3(0, h/2, 0), normal, glm::vec3(0.5, 1, 0)),
			Vertex(glm::vec3(w/2, -h/2, -w/2), normal, glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(-w/2, -h/2, -w/2), normal, glm::vec3(-1, 0, 0)),

			// Left face
			Vertex(glm::vec3(0, h/2, 0), normal, glm::vec3(0.5, 1, 0)),
			Vertex(glm::vec3(-w/2, -h/2, -w/2), normal, glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(-w/2, -h/2, w/2), normal, glm::vec3(-1, 0, 0)),

			// Bottom
			Vertex(glm::vec3(w/2, -h/2, w/2), normal, glm::vec3(0.5, 1, 0)),
			Vertex(glm::vec3(-w/2, -h/2, -w/2), normal, glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(w/2, -h/2, -w/2), normal, glm::vec3(-1, 0, 0)),

			Vertex(glm::vec3(w/2, -h/2, w/2), normal, glm::vec3(0.5, 1, 0)),
			Vertex(glm::vec3(-w/2, -h/2, w/2), normal, glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(-w/2, -h/2, -w/2), normal, glm::vec3(-1, 0, 0)),
		};

		// Calculate normals
		for (std::size_t i = 0; i < pyramid.size(); i += 3)
		{
			glm::vec3 a = pyramid[i + 1].position - pyramid[i].position;
			glm::vec3 b = pyramid[i + 2].position - pyramid[i].position;

			glm::vec3 normal = glm::cross(a, b);

			for (std::size_t j = 0; j < 3; j++)
			{
				pyramid[i + j].normal = normal;
			}
		}

		// Calculate normals
		for (std::size_t i = 0; i < pyramid.size(); i += 3)
		{
			glm::vec3 a = pyramid[i + 1].position - pyramid[i].position;
			glm::vec3 b = pyramid[i + 2].position - pyramid[i].position;
			glm::vec3 n = pyramid[i].normal;

			std::cout << "Normal " << i << ": " << n.x << " " << n.y << " " << n.z << '\n';

		}

		return pyramid;
	}
};


#endif




