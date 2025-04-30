#pragma once

#include "RendererAPI.h"

#include <glm/glm.hpp>

namespace LE
{
	class RenderCommand
	{
	public:

		inline static void SetClearColor(const glm::vec4& Color)
		{
			s_RenderAPI->SetClearColor(Color);
		}

		inline static void Clear()
		{
			s_RenderAPI->Clear();
		}

		inline static void DrawIndexed(const TSharedPtr<VertexArray>& VertexArray)
		{
			s_RenderAPI->DrawIndexed(VertexArray);
		}

	private:

		static RendererAPI* s_RenderAPI;
	};
}