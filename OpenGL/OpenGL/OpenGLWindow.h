#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

using namespace glm;

class OpenGLWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();

	int Init(int width, int height, char* name);
	void Loop();

private:
	GLFWwindow* m_wind;
};

