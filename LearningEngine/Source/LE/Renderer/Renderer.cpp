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

	void Renderer::SubmitObj(const std::shared_ptr<RenderingObject>& RenderingObject)
	{
		RenderingObject->GetRenderingObjectData().Shader->Bind();
		RenderingObject->GetRenderingObjectData().Shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		RenderingObject->GetRenderingObjectData().Shader->UploadUniformMat4("u_Model", RenderingObject->GetRenderingObjectData().ModelMatrix);

		RenderingObject->GetRenderingObjectData().VertexArray->Bind();
		RenderCommand::DrawIndexed(RenderingObject->GetRenderingObjectData().VertexArray);
	}

}