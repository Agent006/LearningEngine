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

		virtual void UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix) const override;

	private:

		uint32_t m_RendererId = 0;
	};
}