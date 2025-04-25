#include "LEpch.h"
#include "Renderer.h"


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

	void Renderer::Submit(const std::shared_ptr<Shader>& Shader, const std::shared_ptr<VertexArray>& VertexArray)
	{
		Shader->Bind();
		Shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		VertexArray->Bind();
		RenderCommand::DrawIndexed(VertexArray);
	}
}