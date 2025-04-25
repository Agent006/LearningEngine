#pragma once

#include "RenderCommand.h"
#include "RendererAPI.h"

#include "VertexArray.h"

namespace LE
{
	class Renderer
	{
	public:

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& VertexArray);

		inline static RendererAPI::API GetAPI()
		{
			return RendererAPI::GetAPI();
		}

	private:


	};
}