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

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	GLuint programID = ShaderLoader::LoadShaders("VertexShader.vs", "FragmentShader.fs");

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 mvp = projection * view * model;

	EzCube* tri = new EzCube();
	tri->Init();


	do {
		//drawing
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		tri->Draw();

		glfwSwapBuffers(m_wind);
		glfwPollEvents();
	} while (glfwGetKey(m_wind, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_wind) == GL_FALSE);

	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	delete tri;
}


