#pragma once
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <stdio.h>

namespace Controls {
	
	void ComputeMatrices(GLFWwindow* window);
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
}