#include "LEpch.h"
#include "Buffers.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffers.h"

namespace LE
{
	TSharedPtr<VertexBuffer> VertexBuffer::Create(float* Vertices, uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return MakeShared<OpenGLVertexBuffer>(Vertices, Size);
			}
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI selected!");
		return nullptr;
	}

	TSharedPtr<IndexBuffer> IndexBuffer::Create(uint32_t* Indices, uint32_t Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return MakeShared<OpenGLIndexBuffer>(Indices, Size);
			}
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI selected!");
		return nullptr;
	}
}