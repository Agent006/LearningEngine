#include "SnakePart.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace LE;

SnakePart::SnakePart(SnakePartMoveType MovementDir, const glm::mat4& OwnerTranslation, std::vector<SnakePartMove> CachedMoves)
	: m_MovementDir(MovementDir), m_CachedMoves(CachedMoves)
{
	std::string vertexShader = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Model;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.f);
			}
		)";

	std::string fragmentShader = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
		
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";


	float vb[4 * 7] =
	{
		-0.05f, -0.05f, 0.0f, 1.f, 0.5f, 0.5f, 1.f,
		 0.05f, -0.05f, 0.0f, 0.5f, 1.f, 0.5f, 1.f,
		 0.05f,  0.05f, 0.0f, 0.2f, 0.5f, 0.2f, 1.f,
		-0.05f,  0.05f, 0.0f, 0.f, 0.f, 1.f, 1.f,
	};

	uint32_t ib[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	VertexBufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position", false },
		{ ShaderDataType::Float4, "a_Color", false }
	};

	m_RenderingObjectData.Shader.reset(Shader::Create(vertexShader, fragmentShader));

	m_RenderingObjectData.VertexArray.reset(VertexArray::Create());
	m_RenderingObjectData.VertexArray->Bind();

	m_RenderingObjectData.VertexBuffer.reset(VertexBuffer::Create(vb, sizeof(vb)));
	m_RenderingObjectData.VertexBuffer->SetLayout(layout);

	m_RenderingObjectData.VertexArray->AddVertexBuffer(m_RenderingObjectData.VertexBuffer);

	m_RenderingObjectData.IndexBuffer.reset(IndexBuffer::Create(ib, 6));
	m_RenderingObjectData.VertexArray->SetIndexBuffer(m_RenderingObjectData.IndexBuffer);

	m_RenderingObjectData.VertexArray->Unbind();

	switch (m_MovementDir)
	{
		case SnakePartMoveType::Forward:	SetModelMatrix(glm::translate(OwnerTranslation, glm::vec3(0.f, -0.2f, 0.f))); break;
		case SnakePartMoveType::Backward:	SetModelMatrix(glm::translate(OwnerTranslation, glm::vec3(0.f, 0.2f, 0.f))); break;
		case SnakePartMoveType::Left:		SetModelMatrix(glm::translate(OwnerTranslation, glm::vec3(0.2f, 0.f, 0.f))); break;
		case SnakePartMoveType::Right:		SetModelMatrix(glm::translate(OwnerTranslation, glm::vec3(-0.2f, 0.f, 0.f))); break;
	}
}

SnakePart::~SnakePart()
{

}

void SnakePart::AddMove(const SnakePartMove& NewMove)
{
	m_CachedMoves.push_back(NewMove);
}

void SnakePart::ExecuteMovement()
{
	switch (m_MovementDir)
	{
		case SnakePartMoveType::Forward:
		{
			SetModelMatrix(glm::translate(GetModelMatrix(), glm::vec3(0.f, 1e-3, 0.f)));
			break;
		}
		case SnakePartMoveType::Backward:
		{
			SetModelMatrix(glm::translate(GetModelMatrix(), glm::vec3(0.f, -1e-3, 0.f)));
			break;
		}
		case SnakePartMoveType::Left:
		{
			SetModelMatrix(glm::translate(GetModelMatrix(), glm::vec3(-1e-3, 0.f, 0.f)));
			break;
		}
		case SnakePartMoveType::Right:
		{
			SetModelMatrix(glm::translate(GetModelMatrix(), glm::vec3(1e-3, 0.f, 0.f)));
			break;
		}
	}
}

void SnakePart::CheckAndExecuteMoves()
{
	if (m_CachedMoves.size() > 0 && glm::length(m_CachedMoves[0].Translation[3] - GetModelMatrix()[3]) <= 1e-5)
	{
		m_MovementDir = m_CachedMoves[0].MoveType;
		m_CachedMoves.erase(m_CachedMoves.begin());
	}
}