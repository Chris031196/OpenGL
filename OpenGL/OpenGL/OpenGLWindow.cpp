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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4); // Version 3.3
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
	glfwSetInputMode(m_wind, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glfwSwapInterval(1);

	//Init OpenGL
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = Loader::LoadShaders("VertexShader.vs", "FragmentShader.fs");

	GLuint id_MVP = glGetUniformLocation(programID, "MVP");
	GLuint id_M = glGetUniformLocation(programID, "M");
	GLuint id_V = glGetUniformLocation(programID, "V");
	GLuint id_P = glGetUniformLocation(programID, "P");
	GLuint id_lightPosition_Worldspace = glGetUniformLocation(programID, "lightPosition_Worldspace");
	GLuint id_texSampler = glGetUniformLocation(programID, "texSampler");
	GLuint id_drawTail = glGetUniformLocation(programID, "in_drawTail");

	glm::vec3 light = glm::vec3(0, 0, 0);
	float grad = 0.0f;

	MeshHolder* mesh = new MeshHolder();
	mesh->initMesh("planet.obj", "texture.bmp");

	std::vector<Planet*> planets;

	Planet* p = new Planet(mesh, 2.0f, glm::vec3(-50.0f, -50.0f, 0.0f)); //, glm::vec3(0.0f, 0.0f, 0.5f)
	Planet* sun = new Planet(mesh, 5.0f, glm::vec3(50.0f, -50.0f, 0.0f));

	planets.push_back(p);
	planets.push_back(sun);

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	do {
		//drawing
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
											 // printf and reset timer
			printf("\n%f ms/frame", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		Controls::ComputeMatrices(m_wind);

		glm::mat4 view = Controls::GetViewMatrix();
		glUniformMatrix4fv(id_V, 1, GL_FALSE, &view[0][0]);
		glm::mat4 projection = Controls::GetProjectionMatrix();
		glUniformMatrix4fv(id_P, 1, GL_FALSE, &projection[0][0]);

		glUniform3fv(id_lightPosition_Worldspace, 1, &light[0]);

		for (int i = 0; i < planets.size(); i++) {
			planets[i]->calculate(planets);
		}

		for (int i = 0; i < planets.size(); i++) {
			planets[i]->update();

			glm::mat4 model = planets[i]->getModelMatrix();
			glm::mat4 mvp = projection * view * model;
			glUniformMatrix4fv(id_M, 1, GL_FALSE, &model[0][0]);
			glUniformMatrix4fv(id_MVP, 1, GL_FALSE, &mvp[0][0]);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->getTexID());
			glUniform1i(id_texSampler, 0);

			planets[i]->Draw(id_drawTail);
		}

		glfwSwapBuffers(m_wind);
		glfwPollEvents();
	} while (glfwGetKey(m_wind, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_wind) == GL_FALSE);


	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteTextures(1, &id_texSampler);
	glDeleteVertexArrays(1, &VertexArrayID);

	for (int i = 0; i < planets.size(); i++) {
		delete planets[i];
	}
	delete mesh;

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	getchar();
}


