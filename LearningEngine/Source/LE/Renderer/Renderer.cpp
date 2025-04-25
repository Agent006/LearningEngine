#include "LEpch.h"
#include "Renderer.h"

namespace LE
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& VertexArray)
	{
		VertexArray->Bind();
		RenderCommand::DrawIndexed(VertexArray);
	}
}