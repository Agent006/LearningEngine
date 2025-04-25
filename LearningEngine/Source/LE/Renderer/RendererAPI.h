#pragma once

#include <glm/glm.hpp>
#include "LE/Renderer/VertexArray.h"

namespace LE
{
	class RendererAPI
	{
	public:

		enum class API
		{
			None = 0,
			OpenGL
		};

	public:

		virtual void SetClearColor(const glm::vec4& Color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& VertexArray) = 0;

		inline static API GetAPI()
		{
			return s_API;
		}

	private:

		static API s_API;
	};
}