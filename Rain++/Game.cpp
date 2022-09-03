#include "Game.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Game::Game(GLFWwindow* window)
	: m_window(window),
	m_physics(PhysicsSystem::instance()),
	m_rain(m_physics, glm::vec3(0.0f), 10.0f, 10.0f),
	m_rainShader("rain.vs", "rain.fs"),
	m_camera(glm::vec3(0.0f, 10.0f, 10.0f))
{
	m_camera.ProcessMouseMovement(0, -10);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

Game::~Game()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool Game::isRunning()
{
	return !glfwWindowShouldClose(m_window);
}

// TODO: Make some kind of input object that contains latest information about keyboard and mouse?
void Game::handleInput(float frameTime)
{
    // tell GLFW to capture our mouse
	static bool enterPressed = false;
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		if (!enterPressed) {
			if (m_enableCursor)
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			m_enableCursor = !m_enableCursor;
		}
		enterPressed = true;
	}
	else {
		enterPressed = false;
	}


	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
		m_camera.ProcessKeyboard(Camera_Movement::FORWARD, frameTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
		m_camera.ProcessKeyboard(Camera_Movement::RIGHT, frameTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
		m_camera.ProcessKeyboard(Camera_Movement::BACKWARD, frameTime);
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
		m_camera.ProcessKeyboard(Camera_Movement::LEFT, frameTime);
	}

	static bool firstFrame = true;
	static glm::vec<2, double> cursorPosLast(-1.0f, -1.0f);
	glm::vec<2, double> cursorPosCur;
	glfwGetCursorPos(m_window, &cursorPosCur.x, &cursorPosCur.y);
	if (firstFrame)
	{
		cursorPosLast = cursorPosCur;
		firstFrame = false;
	}
	glm::vec<2, double> cursorOffset = cursorPosCur - cursorPosLast;
	cursorPosLast = cursorPosCur;

	if (!m_enableCursor)
		m_camera.ProcessMouseMovement(static_cast<float>(cursorOffset.x), static_cast<float>(- cursorOffset.y));
}

void Game::update(float frameTime)
{
	m_physics.update(frameTime);
	m_rain.update(frameTime);
	updateGui();
}

void Game::updateGui()
{
	// Start new ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Rain controller");

	glm::vec3 rainPos = m_rain.getCenter();
	ImGui::DragFloat3("Position", &rainPos[0], 1.0f, -100, 100);
	m_rain.setCenter(rainPos);

	static float intensity = 0.1f;
	ImGui::SliderFloat("Intensity", &intensity, 0.0f, 10.0f);
	m_rain.setIntensity(intensity);

	float radius = m_rain.getRadius();
	ImGui::SliderFloat("Radius", &radius, 0.0f, 50.0f);
	m_rain.setRadius(radius);

	static glm::vec3 gravity = glm::vec3(0.0f, -3.0f, 0.0f);
	ImGui::DragFloat3("Gravity", &gravity[0], 0.1f, -10.0f, 10.0f);
	m_physics.setGravity(gravity);

	ImGui::End();
}

void Game::render()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	glm::mat4 projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f, 100.0f);
	glm::mat4 view = m_camera.GetViewMatrix();
	m_rainShader.use();
	m_rainShader.setMat4("projection", projection);
	m_rainShader.setMat4("view", view);

	float r = 5.0f;
	float t = (float) glfwGetTime();
	m_rainShader.setVec3("lightPos", glm::vec3(r * sin(t), r, r * cos(t)));

	m_rain.draw(m_rainShader);

	m_ground.draw(m_rainShader);

	renderGui();
}

void Game::renderGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
