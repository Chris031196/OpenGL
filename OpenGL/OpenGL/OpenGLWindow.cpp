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

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	//Init OpenGL
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = Loader::LoadShaders("VertexShader.vs", "FragmentShader.fs");

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	

	EzCube* cube = new EzCube();
	GLuint texture = cube->Init();

	GLuint TextureID = glGetUniformLocation(programID, "texSampler");

	do {
		//drawing
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		Controls::ComputeMatrices(m_wind);
		glm::mat4 projection = Controls::GetProjectionMatrix();
		glm::mat4 view = Controls::GetViewMatrix();

		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				glm::mat4 model = glm::translate(glm::vec3(-4.0f*i, 0, -4.0f*j));
				glm::mat4 mvp = projection * view * model;
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture);
				glUniform1i(TextureID, 0);

				cube->Draw();
			}
		}


		glfwSwapBuffers(m_wind);
		glfwPollEvents();
	} while (glfwGetKey(m_wind, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_wind) == GL_FALSE);


	// Cleanup VBO and shader
	delete cube;
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

}


