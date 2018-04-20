#include <vector>
#include <time.h>

#include "src/maths/maths.h"
#include "src/utils/timer.h"
#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"
#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/layers/group.h"
#include "src/graphics/texture.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky window", 1280, 720);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader->enable();
	shader->setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(shader);

	Texture* textures[] =
	{
		new Texture("res/wall.png"),
		new Texture("res/grass.png"),
		new Texture("res/rock.png"),
	};

	int sprites = 0;
	float squareSize = 1.0f;
	for (float y = -9.0f; y < 9.0f; y += squareSize)
	{
		for (float x = -16.0f; x < 16.0f; x += squareSize)
		{
			if (sprites % 2 == 0)
				layer.add(new Sprite(x, y, squareSize - 0.1f, squareSize - 0.1f, textures[rand() % 3]));
			else
				layer.add(new Sprite(x, y, squareSize - 0.1f, squareSize - 0.1f, textures[rand() % 3]));
				// layer.add(new Sprite(x, y, squareSize - 0.1f, squareSize - 0.1f, vec4(0.2f, 0.3f, 0.8f, 1)));
			sprites++;
		}
	}

	GLint texIds[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	shader->enable();
	shader->setUniform1iv("textures", texIds, 10);
	shader->setUniformMat4("pr_matrix", mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

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
		layer.render();
		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			// std::cout << "Timer: " << timer << " | Sprites: " << sprites << " | FPS: " << frames << std::endl;
			frames = 0;
		}
	}

	delete shader;
	for (int i = 0; i < 3; i++)
	{
		delete textures[i];
	}

	return 0;
}
