#include "src/graphics/window.h"
#include "src/maths/maths.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky window", 1280, 720);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	mat4 position = mat4::translation(vec3(2, 3, 4));
	position *= mat4::identity();

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		// std::cout << "X = " << x << " | Y = " << y << std::endl;

		if (window.isKeyPressed(GLFW_KEY_A))
			std::cout << "KEY A PRESSED!" << std::endl;
		if (window.isKeyPressed(GLFW_KEY_D))
			std::cout << "KEY D PRESSED!" << std::endl;
		if (window.isKeyPressed(GLFW_KEY_W))
			std::cout << "KEY W PRESSED!" << std::endl;
		if (window.isKeyPressed(GLFW_KEY_S))
			std::cout << "KEY S PRESSED!" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			std::cout << "LEFT MOUSE BUTTON PRESSED!" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
			std::cout << "MIDDLE MOUSE BUTTON PRESSED!" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
			std::cout << "RIGHT MOUSE BUTTON PRESSED!" << std::endl;

#if 1
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
#endif;

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);

		window.update();
	}

	return 0;
}
