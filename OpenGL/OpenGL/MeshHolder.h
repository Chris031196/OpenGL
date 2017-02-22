#pragma once

#include <GL\glew.h>
#include "GLFW\glfw3.h"
#include "Loader.h"

class MeshHolder
{
public:
	MeshHolder();
	~MeshHolder();

	bool initMesh(char* mesh_path, char* texture_path);
	GLuint getTexID() { return texID;  }

	void Draw();

private:
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;
	GLuint texID;

	std::vector<glm::vec4> indexed_vertices;
	std::vector<glm::vec3>	indexed_normals;
	std::vector<glm::vec2> indexed_uvs;
	int vertex_number;

	bool initialized = false;
};

