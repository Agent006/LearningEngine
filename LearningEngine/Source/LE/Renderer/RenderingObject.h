#pragma once

#include <memory>
#include "LE/Renderer/Shader.h"
#include "LE/Renderer/VertexArray.h"
#include "LE/Renderer/Buffers.h"

#include <glm/glm.hpp>

namespace LE
{
	class RenderingObject
	{
	protected:

		struct RenderingObjectData
		{
			std::shared_ptr<Shader> Shader;
			std::shared_ptr<VertexArray> VertexArray;
			std::shared_ptr<VertexBuffer> VertexBuffer;
			std::shared_ptr<IndexBuffer> IndexBuffer;

			glm::mat4 ModelMatrix = glm::mat4(1.f);
		};

	public:

		virtual ~RenderingObject() {}

		inline const RenderingObjectData& GetRenderingObjectData() const
		{
			return m_RenderingObjectData;
		}

		inline void SetModelMatrix(const glm::mat4& InModelMatrix)
		{
			m_RenderingObjectData.ModelMatrix = InModelMatrix;
		}

		inline const glm::mat4& GetModelMatrix() const
		{
			return m_RenderingObjectData.ModelMatrix;
		}

	protected:

		RenderingObjectData m_RenderingObjectData;
	};
}