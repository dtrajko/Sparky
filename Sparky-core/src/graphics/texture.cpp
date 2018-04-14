#include "texture.h"

namespace sparky { namespace graphics {

	Texture::Texture(const std::string& filename)
		: m_FileName(filename)
	{
		m_TID = load();
	}

	Texture::~Texture()
	{

	}

	GLuint Texture::load()
	{
		BYTE* pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height);
		GLuint tid;
		glGenTextures(1, &tid);
		glBindTexture(GL_TEXTURE_2D, tid);
		glEnable(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
		std::cout << "Filename: " << m_FileName.c_str() << " (" << m_Width << " x " << m_Height  << ")" <<std::endl;
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		// TODO: delete[] pixels
		return tid;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TID);
		glEnable(GL_TEXTURE_2D);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}

} }
