#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include "Loader.h"

class EzCube
{
public:
	EzCube();
	~EzCube();

	GLuint Init();
	void Draw();
	void ChangeColor();

private:
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	int vNum;
};

