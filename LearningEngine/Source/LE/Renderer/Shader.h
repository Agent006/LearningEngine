#pragma once

#include <string>

namespace LE
{
	class Shader
	{
	public:

		Shader(const std::string& VertexShader, const std::string& FragmentShader);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:

		uint32_t m_RendererId;
	};
}