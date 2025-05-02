#pragma once

#include "LE/Renderer/VertexArray.h"

namespace LE
{
	class OpenGLVertexArray : public VertexArray
	{
	public:

		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const TSharedPtr<VertexBuffer>& VertexBuffer) override;
		virtual void SetIndexBuffer(const TSharedPtr<IndexBuffer>& IndexBuffer) override;

		virtual inline const std::vector<TSharedPtr<VertexBuffer>>& GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}

		virtual inline const TSharedPtr<IndexBuffer>& GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}

	private:

		uint32_t m_RendererId;
		uint32_t m_VertexBufferIndexOffset = 0;

		std::vector<TSharedPtr<VertexBuffer>> m_VertexBuffers;
		TSharedPtr<IndexBuffer> m_IndexBuffer;
	};
}