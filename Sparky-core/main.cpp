#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky window", 1280, 720);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vbo;

	GLfloat vertices[] =
	{
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
	// shader.setUniformMat4("ml_matrix", mat4::rotation(45.0f, vec3(0, 0, 1)));

	shader.setUniform2f("light_pos", vec2(4, 1.5));
	shader.setUniform4f("colour", vec4(0.6f, 0.6f, 1.0f, 1.0f));

	/* BEGIN TESTING
	mat4 position = mat4::translation(vec3(2, 3, 4));
	position *= mat4::identity();

	vec4 column = position.columns[2];
	std::cout << "Column3: " << column << std::endl;

	std::string file = read_file("main.cpp");
	std::cout << file << std::endl;
	END TESTING */

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		if (window.isKeyPressed(GLFW_KEY_A))
			std::cout << "KEY A PRESSED!" << std::endl;
		if (window.isKeyPressed(GLFW_KEY_D))
			std::cout << "KEY D PRESSED!" << std::endl;
		if (window.isKeyPressed(GLFW_KEY_W))
			std::cout << "KEY W PRESSED!" << std::endl;
		if (window.isKeyPressed(GLFW_KEY_S))
			std::cout << "KEY S PRESSED!" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			std::cout << "LEFT MOUSE BUTTON PRESSED [X=" << x << ", Y=" << y << "]" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
			std::cout << "MIDDLE MOUSE BUTTON PRESSED [X=" << x << ", Y=" << y << "]" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
			std::cout << "RIGHT MOUSE BUTTON PRESSED [X=" << x << ", Y=" << y << "]" << std::endl;

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();
	}

	return 0;
}
