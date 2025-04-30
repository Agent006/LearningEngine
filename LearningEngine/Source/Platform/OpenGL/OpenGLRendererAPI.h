#pragma once

#include "LE/Renderer/RendererAPI.h"

namespace LE
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:

		OpenGLRendererAPI();

		virtual void SetClearColor(const glm::vec4& Color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const TSharedPtr<VertexArray>& VertexArray) override;
	};
}