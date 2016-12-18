#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "EzTriangle.h"
#include "EzCube.h"
#include "LoadShader.h"


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

