#pragma once

#include "LE/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace LE
{
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& VertexShader, const std::string& FragmentShader);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& Name, int32_t Integer) const;

		void UploadUniformFloat(const std::string& Name, float Value) const;
		void UploadUniformFloat2(const std::string& Name, const glm::vec2& Value) const;
		void UploadUniformFloat3(const std::string& Name, const glm::vec3& Value) const;
		void UploadUniformFloat4(const std::string& Name, const glm::vec4& Value) const;

		void UploadUniformMat3(const std::string& Name, const glm::mat3& Matrix) const;
		void UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix) const;


	private:

		uint32_t m_RendererId = 0;
	};
}