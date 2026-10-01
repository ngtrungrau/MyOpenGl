#include"glew.h"
#include"glfw3.h"
#include "Texture.h"
#include"stb_image.h"
#include "Debug.h"
namespace MyGl
{
	Texture::Texture(const std::string& path):
		m_id(0),m_data(nullptr),m_height(0),m_width(0),m_BPP(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_data= stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
		glCall(glGenTextures(1, &m_id));
		glCall(glBindTexture(GL_TEXTURE_2D, m_id));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data));
		glCall(glBindTexture(GL_TEXTURE_2D, 0));
		if (m_data) stbi_image_free(m_data);

	}
	Texture::~Texture()
	{
		glCall(glDeleteTextures(1, &m_id));
	}
	void Texture::Bind(unsigned int slot) const
	{
		glCall(glActiveTexture(GL_TEXTURE0 + slot));
		glCall(glBindTexture(GL_TEXTURE_2D, m_id));
	}
	void Texture::UnBind() const
	{
		glCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}