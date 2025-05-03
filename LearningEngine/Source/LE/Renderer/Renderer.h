#pragma once

#include "LE/Renderer/RenderCommand.h"
#include "LE/Renderer/RenderCommand.h"

#include "LE/Renderer/VertexArray.h"
#include "LE/Renderer/OrthographicCamera.h"

#include "LE/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace LE
{
	class Renderer
	{
	public:

		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t Width, uint32_t Height);

		static void BeginScene(const OrthographicCamera& Camera);
		static void EndScene();

		static void Submit(const TSharedPtr<Shader>& Shader, const TSharedPtr<VertexArray>& VertexArray, const glm::mat4& Transform);

		inline static RendererAPI::API GetAPI()
		{
			return RendererAPI::GetAPI();
		}

	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static TUniquePtr<SceneData> s_SceneData;
	};
}