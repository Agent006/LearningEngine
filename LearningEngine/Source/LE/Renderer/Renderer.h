#pragma once

#include "RenderCommand.h"
#include "RendererAPI.h"

#include "VertexArray.h"

#include "LE/Renderer/OrthographicCamera.h"

#include "Shader.h"

#include <glm/glm.hpp>

namespace LE
{
	class Renderer
	{
	public:

		static void BeginScene(OrthographicCamera& Camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& VertexArray, const glm::mat4& Transform);

		inline static RendererAPI::API GetAPI()
		{
			return RendererAPI::GetAPI();
		}

	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}