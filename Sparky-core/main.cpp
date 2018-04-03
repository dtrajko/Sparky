#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/renderable2d.h"
#include "src/graphics/simple2drenderer.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky window", 1280, 720);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

#if 0

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

	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};

	GLfloat colorsA[] =
	{
		0.2f, 0.3f, 0.8f, 1,
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1,
	};

	GLfloat colorsB[] =
	{
		1.0f, 0.0f, 0.0f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0, 0, 1, 1,
		0, 1, 0, 1,
	};

	VertexArray sprite1, sprite2;
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

	sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite2.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);

#else
#endif;

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.setUniformMat4("pr_matrix", ortho);

	// shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
	// shader.setUniform2f("light_pos", vec2(4, 1.5));
	// shader.setUniform4f("colour", vec4(0.6f, 0.6f, 1.0f, 1.0f));

	Renderable2D sprite1(maths::vec3(1, 1, 0), maths::vec2(8, 3), maths::vec4(0, 1, 1, 1), shader);
	Renderable2D sprite2(maths::vec3(12, 1, 0), maths::vec2(3, 3), maths::vec4(1, 0, 1, 1), shader);
	Renderable2D sprite3(maths::vec3(1, 5, 0), maths::vec2(6, 3), maths::vec4(0, 0, 1, 1), shader);
	Renderable2D sprite4(maths::vec3(11, 6, 0), maths::vec2(4, 2), maths::vec4(1, 1, 0, 1), shader);

	Simple2DRenderer renderer;

#if 0
	mat4 position = mat4::translation(vec3(2, 3, 4));
	position *= mat4::identity();

	vec4 column = position.columns[2];
	std::cout << "Column3: " << column << std::endl;

	std::string file = read_file("main.cpp");
	std::cout << file << std::endl;
#endif

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

#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);

		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(8, 6, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();
#else
#endif

		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f - 0.0f), (float)((9.0f - y * 9.0f / 720.0f) - 0.0f)));

		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.submit(&sprite3);
		renderer.submit(&sprite4);
		renderer.flush();

		window.update();
	}

	return 0;
}
