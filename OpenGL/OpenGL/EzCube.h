#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

class EzCube
{
public:
	EzCube();
	~EzCube();

	void Init();
	void Draw();

private:
	GLuint vertexBuffer;
	GLuint colorBuffer;
};

