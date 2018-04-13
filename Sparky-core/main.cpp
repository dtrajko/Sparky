#include <vector>
#include <time.h>
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
#include "src/utils/timer.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky window", 960, 540);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader* shader2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader->enable();
	shader2->enable();
	shader->setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader2->setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(shader);
	TileLayer layer2(shader2);

	/*
	int sprites = 0;
	for (float y = -9.0; y < 9.0f; y += 0.2f)
	{
		for (float x = -16.0; x < 16.0f; x += 0.2f)
		{
			layer.add(new Sprite(x, y, 0.18f, 0.18f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			sprites++;
		}
	}
	*/

	mat4 transform = mat4::translation(vec3(-12.0f, 1.0f, 0.0f)) * mat4::rotation(45, vec3(0, 0, 1));
	Group* group = new Group(transform);
	group->add(new Sprite(0.0f, 0.0f, 6, 3, maths::vec4(1, 1, 1, 1)));

	Group* button = new Group(mat4::translation(vec3(0.5f, 0.5f, 0.0f)));
	button->add(new Sprite(0, 0, 5, 2, maths::vec4(1, 0, 1, 1)));
	button->add(new Sprite(0.5f, 0.5f, 4, 1, maths::vec4(0.2f, 0.3f, 0.8f, 1)));
	group->add(button);
	layer.add(group);

	layer.add(new Sprite(-6.0f, -3.0f, 2, 8, maths::vec4(1, 1, 0, 1)));
	layer.add(new Sprite(-3.0f, -3.0f, 8, 8, maths::vec4(0.2f, 0.2f, 0.8f, 1)));

	layer2.add(new Sprite(-2, -2, 4, 4, maths::vec4(1, 0, 1, 1)));

	Texture texture("test.png");
	Simple2DRenderer simple;
	Sprite* testTexture = new Sprite(0, 0, 4, 4, maths::vec4(1, 1, 1, 1));

	double x, y;
	Timer time;
	float timer = 0;
	unsigned int frames = 0;

	while (!window.closed())
	{
		window.clear();
		window.getMousePosition(x, y);
		shader->enable();
		shader->setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		shader2->enable();
		shader2->setUniform2f("light_pos", vec2((float)-(x * 32.0f / window.getWidth() - 16.0f), (float)-(9.0f - y * 18.0f / window.getHeight())));

		layer.render();
		layer2.render();

		simple.submit(testTexture);
		// simple.flush();

		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			std::cout << "Timer: " << timer << " | Sprites: " << "n/a" << " | FPS: " << frames << std::endl;
			frames = 0;
		}
	}

	delete shader;
	delete shader2;

	return 0;
}
