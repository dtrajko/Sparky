#pragma once

#include <GL/glew.h>

namespace sparky { namespace graphics {

	class IndexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;

	public:
		IndexBuffer(GLfloat* data, GLsizei count, GLuint componentCount);

		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return m_ComponentCount; };
	};

} }
