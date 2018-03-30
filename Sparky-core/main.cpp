#include "src/graphics/window.h"

int main()
{
	using namespace sparky;
	using namespace graphics;

	Window window("Sparky window", 1280, 720);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	while (!window.closed())
	{
		window.clear();
		window.update();
	}

	return 0;
}
