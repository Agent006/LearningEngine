#include "LEpch.h"
#include "Buffers.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffers.h"

namespace LE
{
	VertexBuffer* VertexBuffer::Create(float* Vertices, uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
			{
				LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::OpenGL:
			{
				return new OpenGLVertexBuffer(Vertices, Size);
			}
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI selected!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* Indices, uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
			{
				LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::OpenGL:
			{
				return new OpenGLIndexBuffer(Indices, Size);
			}
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI selected!");
		return nullptr;
	}
}