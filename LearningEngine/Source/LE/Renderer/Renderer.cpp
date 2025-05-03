#include "LEpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

// TEMP:
#include "Platform/OpenGL/OpenGLShader.h"

namespace LE
{
	TUniquePtr<Renderer::SceneData> Renderer::s_SceneData = MakeUnique<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t Width, uint32_t Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}

	void Renderer::BeginScene(const OrthographicCamera& Camera)
	{
		s_SceneData->ViewProjectionMatrix = Camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const TSharedPtr<Shader>& Shader, const TSharedPtr<VertexArray>& VertexArray, const glm::mat4& Transform)
	{
		Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(Shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(Shader)->UploadUniformMat4("u_Transform", Transform);

		VertexArray->Bind();
		RenderCommand::DrawIndexed(VertexArray);
	}
}