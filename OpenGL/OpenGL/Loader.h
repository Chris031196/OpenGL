#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>

namespace Loader {
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	unsigned char* LoadBMP(const char* imagepath, int **height, int **width);
	int loadOBJ(const char* path, std::vector <glm::vec3> & out_vertices, std::vector <glm::vec2> & out_uvs, std::vector <glm::vec3>& out_normals);
}