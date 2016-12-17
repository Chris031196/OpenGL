#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow()
{
}


OpenGLWindow::~OpenGLWindow()
{
}

int OpenGLWindow::Init(int width, int height, char * name)
{
	//Init GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to init glfw!");
		return -1;
	}

	//Give GLFW some Info
	glfwWindowHint(GLFW_SAMPLES, 4); //Antialiasing 4x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Version 3.3
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Some Mac Stuff
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Not the old OpenGL

	m_wind = glfwCreateWindow(width, height, name, NULL, NULL);
	if (m_wind == NULL) {
		fprintf(stderr, "Failed to Init Window!");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_wind);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to Init GLEW!");
		getchar();
		glfwTerminate();
		return -1;
	}

	return 0;
}

void OpenGLWindow::Loop()
{
	glfwSetInputMode(m_wind, GLFW_STICKY_KEYS, GL_TRUE);

	//Init OpenGL
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Init coordinates
	GLfloat g_vertex_buffer_data[] = {
		-1.0f,	-1.0f,	0.0f,
		1.0f,	-1.0f,	0.0f,
		0.0f,	1.0f,	0.0f
	};
	
	//Init vertexBuffer
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do {
		//drawing

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Draw Triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(m_wind);
		glfwPollEvents();
	} while (glfwGetKey(m_wind, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_wind) == GL_FALSE);
}


