#include "LEpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace LE
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataType Type)
	{
		switch (Type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		LE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer)
	{
		LE_CORE_ASSERT(VertexBuffer->GetBufferLayout().GetElements().size() > 0, "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererId);
		VertexBuffer->Bind();

		const uint32_t layoutElementsCount = (uint32_t)VertexBuffer->GetBufferLayout().GetElements().size();
		for (uint32_t i = 0; i < layoutElementsCount; i++)
		{
			const BufferElement& element = VertexBuffer->GetBufferLayout().GetElements()[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLDataType(element.Type),
				element.bNormalized ? GL_TRUE : GL_FALSE,
				VertexBuffer->GetBufferLayout().GetStride(),
				(const void*)element.Offset);
		}

		m_VertexBuffers.push_back(VertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer)
	{
		glBindVertexArray(m_RendererId);
		IndexBuffer->Bind();
		m_IndexBuffer = IndexBuffer;
	}
}