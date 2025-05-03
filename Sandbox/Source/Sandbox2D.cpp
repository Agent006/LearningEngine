
#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>

// TEMP:
#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.f)
{
}

void Sandbox2D::OnAttach()
{
	m_Shader = LE::Shader::Create("Assets/Shaders/FlatColorShader.glsl");
	m_VertexArray = LE::VertexArray::Create();

	float vb[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	LE::TSharedPtr<LE::VertexBuffer> vertexBuffer;
	vertexBuffer = LE::VertexBuffer::Create(vb, sizeof(vb));

	LE::VertexBufferLayout layout = {
		{ LE::ShaderDataType::Float3, "a_Position", false }
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t ib[6] = { 0, 1, 2, 2, 3, 0 };
	LE::TSharedPtr<LE::IndexBuffer> indexBuffer;
	indexBuffer = LE::IndexBuffer::Create(ib, 6);
	m_VertexArray->SetIndexBuffer(indexBuffer);
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(LE::Timestep DeltaTime)
{
	m_CameraController.OnUpdate(DeltaTime);

	LE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
	LE::RenderCommand::Clear();

	LE::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<LE::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<LE::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);

	LE::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.f), glm::vec3(0)));

	LE::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorPicker4("SquareColor", &m_SquareColor[0]);
	ImGui::End();
}

void Sandbox2D::OnEvent(LE::Event& e)
{
	LE::EventDispatcher dispatcher(e);
	m_CameraController.OnEvent(e);
}