#pragma once

#include "LE/Renderer/Texture.h"

namespace LE
{
	class OpenGLTexture2D : public Texture2D
	{
	public:

		OpenGLTexture2D(const std::string& Path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t Slot) const override;

	private:

		std::string m_Path;

		uint32_t m_Width = 0;
		uint32_t m_Height = 0;

		uint32_t m_RendererId;
	};
}