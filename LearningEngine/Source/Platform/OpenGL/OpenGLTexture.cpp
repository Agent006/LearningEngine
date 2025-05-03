#include "LEpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace LE
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t Width, uint32_t Height)
		: m_Width(Width), m_Height(Height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& Path)
		: m_Path(Path)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		stbi_uc* data = stbi_load(Path.c_str(), &width, &height, &channels, 0);
		LE_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		if (channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}
		else if (channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}

		LE_CORE_ASSERT(m_InternalFormat && m_DataFormat, "Texture format is not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		SetData(data, sizeof(data));

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGLTexture2D::Bind(uint32_t Slot) const
	{
		glBindTextureUnit(Slot, m_RendererId);
	}

	void OpenGLTexture2D::SetData(void* Data, size_t Size)
	{
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, Data);
	}
}