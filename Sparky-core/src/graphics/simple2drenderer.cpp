#include "simple2drenderer.h"

namespace sparky { namespace graphics {

	void Simple2DRenderer::submit(const Renderable2D* renderable)
	{
		m_RenderQueue.push_back(renderable);
	}
	void Simple2DRenderer::flush()
	{
		while (!m_RenderQueue.empty())
		{
			const Renderable2D* renderable = m_RenderQueue.front();

			const VertexArray* vao = renderable->getVAO();
			const IndexBuffer* ibo = renderable->getIBO();
			Shader shader = renderable->getShader();

			vao->bind();
			ibo->bind();

			shader.setUniformMat4("ml_matrix", maths::mat4::translation(renderable->getPosition()));
			glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_SHORT, nullptr);

			ibo->unbind();
			vao->unbind();

			m_RenderQueue.pop_front();
		}
	}

} }
