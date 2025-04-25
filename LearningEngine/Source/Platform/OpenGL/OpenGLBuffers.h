#pragma once

#include "LE/Renderer/Buffers.h"

namespace LE
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(float* Vertices, uint32_t Size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:

		uint32_t m_RendererId;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:

		OpenGLIndexBuffer(uint32_t* Indices, uint32_t Count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override
		{
			return m_Count;
		}

	private:

		uint32_t m_RendererId;
		uint32_t m_Count;
	};
}