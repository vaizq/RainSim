#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Rain.h"
#include "Shader.h"
#include "Camera.h"
#include "Ground.h"

#include <GLFW/glfw3.h>

class Game
{
public:
	Game(GLFWwindow* window);
	~Game();
	bool isRunning();
	void handleInput(float frameTime);
	void update(float frameTime);
	void render();
private:
	void updateGui();
	void renderGui();
	GLFWwindow* m_window;
	Camera m_camera;
	PhysicsSystem& m_physics;
	Rain m_rain;
	Shader m_rainShader;
	Ground m_ground;
	bool m_enableCursor = false;
};

