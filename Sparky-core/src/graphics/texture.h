#pragma once

#include <string>
#include <iostream>
#include <GL/glew.h>
#include "../utils/ImageLoad.h"

namespace sparky { namespace graphics {

	class Texture
	{
	private:
		std::string m_FileName;
		GLuint m_TID;
		GLsizei m_Width, m_Height;

	public:
		Texture(const std::string& filename);
		~Texture();

		void bind() const;
		void unbind() const;

		inline const GLuint getID() const { return m_TID; };
		inline const GLuint getWidth() const { return m_Width; };
		inline const GLuint getHeight() const { return m_Height; };

	private:
		GLuint load();
	};

} }
