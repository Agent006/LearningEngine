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

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) override;

		virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}

		virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}

	private:

		uint32_t m_RendererId;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}