#include "OpenGLWindow.h"

int main()
{
	OpenGLWindow window = OpenGLWindow();
	if (window.Init(1920, 1080, "OpenGL Window") == 0) {
		window.Loop();
	}

    return 0;
}