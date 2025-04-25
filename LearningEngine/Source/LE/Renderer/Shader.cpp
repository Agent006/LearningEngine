#include "LEpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace LE
{
	Shader* Shader::Create(const std::string& VertexShader, const std::string& FragmentShader)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLShader(VertexShader, FragmentShader);
			}
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI selected!");
		return nullptr;
	}
}