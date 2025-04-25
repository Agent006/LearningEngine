#pragma once

#include <string>

namespace LE
{
	class Shader
	{
	public:

		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& VertexShader, const std::string& FragmentShader);
	};
}