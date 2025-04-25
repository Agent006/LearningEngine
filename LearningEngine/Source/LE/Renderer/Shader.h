#pragma once

#include <string>
#include <glm/glm.hpp>

namespace LE
{
	class Shader
	{
	public:

		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix) const = 0;

		static Shader* Create(const std::string& VertexShader, const std::string& FragmentShader);
	};
}