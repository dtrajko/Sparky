#include "simple2drenderer.h"

namespace sparky { namespace graphics {

	void Simple2DRenderer::submit(const Renderable2D* renderable)
	{
		m_RenderQueue.push_back((StaticSprite*) renderable);
	}

	void Simple2DRenderer::flush()
	{
		while (!m_RenderQueue.empty())
		{
			const StaticSprite* sprite = m_RenderQueue.front();

			const VertexArray* vao = sprite->getVAO();
			const IndexBuffer* ibo = sprite->getIBO();
			Shader shader = sprite->getShader();

			vao->bind();
			ibo->bind();

			shader.setUniformMat4("ml_matrix", maths::mat4::translation(sprite->getPosition()));
			glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr);

			ibo->unbind();
			vao->unbind();

			m_RenderQueue.pop_front();
		}
	}

} }
