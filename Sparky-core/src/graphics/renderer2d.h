#pragma once

#include <GL/glew.h>
#include "../maths/maths.h"
#include "static_sprite.h"

namespace sparky { namespace graphics {

		class Renderer2D
		{
		public:
			virtual void submit(const StaticSprite* renderable) = 0;
			virtual void flush() = 0;
		};


} }
