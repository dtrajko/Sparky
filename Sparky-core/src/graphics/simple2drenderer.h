#pragma once

#include <deque>
#include "renderer2d.h"
#include "static_sprite.h"

namespace sparky { namespace graphics {

	class Simple2DRenderer : public Renderer2D
	{
	private:
		std::deque<const StaticSprite*> m_RenderQueue;

	public:
		inline void begin() {};
		void submit(const Renderable2D* renderable) override;
		void flush() override;
		inline void end() {};

	};

} }
