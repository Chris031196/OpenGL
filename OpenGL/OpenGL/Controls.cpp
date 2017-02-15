#include "Controls.h"

glm::mat4 proMat;
glm::mat4 viewMat;

glm::vec3 position = glm::vec3(0, 0, 0);
float horizontalAngle = glm::radians(90.0f);
float verticalAngle = 0.0f;
float initialFov = glm::radians(75.0f);
float speedN = 3.0f;
float mouseSpeed = 0.05f;

float lastTime = glfwGetTime();

void Controls::ComputeMatrices(GLFWwindow* window)
{
	float deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();

	double mX, mY;
	glfwGetCursorPos(window, &mX, &mY);
	glfwSetCursorPos(window, 1920.0/2.0, 1080.0/2.0);

	horizontalAngle += mouseSpeed * deltaTime * float(1920.0 / 2.0 - mX);
	verticalAngle += mouseSpeed * deltaTime * float(1080.0 / 2.0 - mY);

	if (verticalAngle <= glm::radians(-90.0f)) {
		verticalAngle = glm::radians(-90.0f);
	}
	if (verticalAngle >= glm::radians(90.0f)) {
		verticalAngle = glm::radians(90.0f);
	}

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - glm::radians(90.0f)),
		0,
		cos(horizontalAngle - glm::radians(90.0f))
	);

	glm::vec3 up = glm::cross(right, direction);

	float speed = speedN;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = speedN*2;
	}
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += glm::vec3(0, 1, 0) * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position -= glm::vec3(0, 1, 0) * deltaTime * speed;
	}

	proMat = glm::perspective(initialFov, 16.0f / 9.0f, 0.1f, 100.0f);
	viewMat = glm::lookAt(position, position + direction, up);

}

glm::mat4 Controls::GetProjectionMatrix()
{
	return proMat;
}

glm::mat4 Controls::GetViewMatrix()
{
	return viewMat;
}
