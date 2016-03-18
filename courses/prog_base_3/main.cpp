#include "MainHeaders.h"

const GLuint WIDTH = 800, HEIGHT = 600;
#define arr_size(a) sizeof(a)/sizeof(a[0])
// The MAIN function, from here we start the application and run the game loop
int main()
{
	bool close = false;
	Window window = Window(HEIGHT, WIDTH);
	window.open();
	Loader loader = Loader();
	Renderer renderer = Renderer();
	GLfloat vertices[] = {  -0.5f, 0.5f, 0.0f,
							-0.5f, -0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
							0.5f, 0.5f, 0.0f,
							-0.5f, 0.5f, 0.0f}; // QUAD
	Model quad = loader.loadToVao(vertices, arr_size(vertices));
	while (!close)
	{
		//i++;
		if (_kbhit())
			if (_getch() == 'q')
				close = true;
		renderer.prepare();
		renderer.render(quad);
		window.update();
	}
	loader.releaseVOs();
	window.close();
	_getch();
	return 0;
}