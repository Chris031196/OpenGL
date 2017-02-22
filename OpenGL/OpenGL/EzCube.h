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
	GLuint indexBuffer;

	std::vector<glm::vec4> indexed_vertices;
	std::vector<glm::vec3> indexed_normals;
	std::vector<glm::vec2> indexed_uvs;
	int vNum;
};

