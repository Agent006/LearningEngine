#include "LEpch.h"
#include "VertexBufferLayout.h"

namespace LE
{
	VertexBufferLayout::VertexBufferLayout(const std::initializer_list<BufferElement>& InElements)
		: m_Elements(InElements)
	{
		CalculateOffsetsAndStride();
	}

	void VertexBufferLayout::CalculateOffsetsAndStride()
	{
		m_Stride = 0;
		for (BufferElement& element : m_Elements)
		{
			element.Offset = m_Stride;
			m_Stride += element.Size;
		}
	}
}