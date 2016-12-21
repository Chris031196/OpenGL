#pragma once

#include <GL\glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>

namespace Loader {
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	unsigned char* LoadBMP(const char* imagepath, unsigned int **height, unsigned int **width);
}