#include "OpenGLWindow.h"

int main()
{
	OpenGLWindow* window = new OpenGLWindow();
	if (window->Init(1920, 1080, "OpenGL Window") == 0) {
		window->Loop();
	}

	delete window;
    return 0;
}