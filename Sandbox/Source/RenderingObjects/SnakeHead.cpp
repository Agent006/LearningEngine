#include "SnakeHead.h"

using namespace LE;

SnakeHead::SnakeHead()
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


	float vb[3 * 4] =
	{
		-0.1f, -0.1f, 0.0f,
		 0.1f, -0.1f, 0.0f,
		 0.1f,  0.1f, 0.0f,
		-0.1f,  0.1f, 0.0f
	};

	uint32_t ib[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	VertexBufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position", false },
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
}

SnakeHead::~SnakeHead()
{

}