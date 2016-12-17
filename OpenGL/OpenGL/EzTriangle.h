#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class EzTriangle
{
public:
	EzTriangle();
	~EzTriangle();

	void Init();
	void Draw();

private:
	GLuint vertexBuffer;
};

