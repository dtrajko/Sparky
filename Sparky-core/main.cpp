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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.setUniformMat4("pr_matrix", ortho);

	Renderable2D sprite1(maths::vec3(1, 1, 0), maths::vec2(8, 3), maths::vec4(0.5, 1, 1, 1), shader);
	Renderable2D sprite2(maths::vec3(12, 1, 0), maths::vec2(3, 3), maths::vec4(1, 0.5, 1, 1), shader);
	Renderable2D sprite3(maths::vec3(1, 5, 0), maths::vec2(6, 3), maths::vec4(0.5, 0.5, 1, 1), shader);
	Renderable2D sprite4(maths::vec3(11, 6, 0), maths::vec2(4, 2), maths::vec4(1, 1, 0.5, 1), shader);

	Simple2DRenderer renderer;

	double x, y;
	double light_x, light_y;

	light_x = 8;
	light_y = 4.5;

	while (!window.closed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_A))
		{
			std::cout << "KEY A PRESSED!" << std::endl;
			light_x -= 1;
		}
		if (window.isKeyPressed(GLFW_KEY_D))
		{
			std::cout << "KEY D PRESSED!" << std::endl;
			light_x += 1;
		} 
		if (window.isKeyPressed(GLFW_KEY_W))
		{
			std::cout << "KEY W PRESSED!" << std::endl;
			light_y -= 1;
		}
		if (window.isKeyPressed(GLFW_KEY_S))
		{
			std::cout << "KEY S PRESSED!" << std::endl;
			light_y += 1;
		}

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			window.getMousePosition(x, y);
			std::cout << "LEFT MOUSE BUTTON PRESSED [X=" << x << ", Y=" << y << "]" << std::endl;
			light_x = x;
			light_y = y;
		}
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
			std::cout << "MIDDLE MOUSE BUTTON PRESSED [X=" << x << ", Y=" << y << "]" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
			std::cout << "RIGHT MOUSE BUTTON PRESSED [X=" << x << ", Y=" << y << "]" << std::endl;

		shader.setUniform2f("light_pos", vec2((float)(light_x * 16.0f / window.getWidth() - 0.0f), (float)((9.0f - light_y * 9.0f / window.getHeight()) - 0.0f)));

		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.submit(&sprite3);
		renderer.submit(&sprite4);
		renderer.flush();

		window.update();
	}

	return 0;
}
