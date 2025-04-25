#pragma once

#include "VertexBufferLayout.h"

namespace LE
{
	class VertexBuffer
	{
	public:

		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual inline const VertexBufferLayout& GetBufferLayout() const = 0;
		virtual void SetLayout(const VertexBufferLayout& Layout) = 0;

		static VertexBuffer* Create(float* Vertices, uint32_t Size);
	};

	class IndexBuffer
	{
	public:

		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* Indices, uint32_t Size);
	};
}