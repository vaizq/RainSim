#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <vector>
#include "Shader.h"


struct Vertex 
{
    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec3 texCoords)
        : position(pos), normal(normal), texCoords(texCoords)
    {}
    // position
    glm::vec3 position;
    // normal
    glm::vec3 normal;
    // texCoords
    glm::vec2 texCoords;
};


struct Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices);
    void draw(const Shader& shader);
private:
    GLuint m_vertexCount;
    GLuint m_vao, m_vbo;
};

#endif
