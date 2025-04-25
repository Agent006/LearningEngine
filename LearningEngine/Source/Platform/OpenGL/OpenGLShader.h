#pragma once

#include "LE/Renderer/Shader.h"

namespace LE
{
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& VertexShader, const std::string& FragmentShader);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:

		uint32_t m_RendererId = 0;
	};
}