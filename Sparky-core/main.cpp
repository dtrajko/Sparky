#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include <vector>
#include <time.h>

#define BATCH_RENDERER 1

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky window", 1280, 720);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	std::vector<Renderable2D*> sprites;

	srand((unsigned int)time(NULL));

	for (float y = 0; y < 9.0f; y += 0.06f)
	{
		for (float x = 0; x < 16.0f; x += 0.06f)
		{
			#if BATCH_RENDERER
			sprites.push_back(new Sprite(x, y, 0.05f, 0.05f, maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1, 1)));
			#else
			sprites.push_back(new StaticSprite(x, y, 0.05f, 0.05f, maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1, 1), shader));
			#endif
		}
	}

	std::cout << "Number of sprites: " << sprites.size() << std::endl;

	#if BATCH_RENDERER

	Sprite sprite1( 1, 1, 8, 3, maths::vec4(0.5,   1,   1, 1));
	Sprite sprite2(12, 1, 3, 3, maths::vec4(  1, 0.5,   1, 1));
	Sprite sprite3( 1, 5, 6, 3, maths::vec4(0.5, 0.5,   1, 1));
	Sprite sprite4(11, 6, 4, 2, maths::vec4(  1,   1, 0.5, 1));
	BatchRenderer2D renderer;

	#else

	StaticSprite sprite1( 1, 1, 8, 3, maths::vec4(0.5,   1,   1, 1), shader);
	StaticSprite sprite2(12, 1, 3, 3, maths::vec4(  1, 0.5,   1, 1), shader);
	StaticSprite sprite3( 1, 5, 6, 3, maths::vec4(0.5, 0.5,   1, 1), shader);
	StaticSprite sprite4(11, 6, 4, 2, maths::vec4(  1,   1, 0.5, 1), shader);
	Simple2DRenderer renderer;

	#endif

	double x, y;
	double light_x, light_y;

	light_x = 8;
	light_y = 4.5;

	#define LIGHT_SPEED 20;

	while (!window.closed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_A))
			light_x -= 0.5f * LIGHT_SPEED;
		if (window.isKeyPressed(GLFW_KEY_D))
			light_x += 0.5f * LIGHT_SPEED;
		if (window.isKeyPressed(GLFW_KEY_W))
			light_y -= 0.5f * LIGHT_SPEED;
		if (window.isKeyPressed(GLFW_KEY_S))
			light_y += 0.5f * LIGHT_SPEED;

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || 
			window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE) ||
			window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
		{
			window.getMousePosition(x, y);
			light_x = x;
			light_y = y;
		}

		shader.setUniform2f("light_pos", vec2((float)(light_x * 16.0f / window.getWidth() - 0.0f), (float)((9.0f - light_y * 9.0f / window.getHeight()) - 0.0f)));

		renderer.begin();

		for (unsigned int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}

		renderer.end();
		renderer.flush();

		window.update();
	}

	return 0;
}
