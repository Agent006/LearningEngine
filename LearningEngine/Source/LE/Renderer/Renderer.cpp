#include "LEpch.h"
#include "Renderer.h"

// TEMP:
#include "Platform/OpenGL/OpenGLShader.h"

namespace LE
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& Camera)
	{
		m_SceneData->ViewProjectionMatrix = Camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const TSharedPtr<Shader>& Shader, const TSharedPtr<VertexArray>& VertexArray, const glm::mat4& Transform)
	{
		Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(Shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(Shader)->UploadUniformMat4("u_Transform", Transform);

		VertexArray->Bind();
		RenderCommand::DrawIndexed(VertexArray);
	}
}