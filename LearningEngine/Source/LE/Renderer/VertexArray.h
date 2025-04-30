#pragma once

#include "LE/Renderer/Buffers.h"
#include <memory>

namespace LE
{
	class VertexArray
	{
	public:

		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const TSharedPtr<VertexBuffer>& VertexBuffer) = 0;
		virtual void SetIndexBuffer(const TSharedPtr<IndexBuffer>& IndexBuffer) = 0;

		virtual inline const std::vector<TSharedPtr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual inline const TSharedPtr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}