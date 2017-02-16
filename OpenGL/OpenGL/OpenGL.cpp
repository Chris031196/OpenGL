#include "OpenGLWindow.h"
#include "WindowData.h"

int main()
{
	OpenGLWindow window = OpenGLWindow();
	if (window.Init(WindowData::width, WindowData::height, "OpenGL Window") == 0) {
		window.Loop();
	}

    return 0;
}