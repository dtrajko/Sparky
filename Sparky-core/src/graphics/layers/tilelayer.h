#pragma once

#include "../renderer2d.h"
#include "../renderable2d.h"
#include "layer.h"
#include "../batchrenderer2d.h"

namespace sparky { namespace graphics {

	class TileLayer : public Layer
	{
	protected:
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};

} }
