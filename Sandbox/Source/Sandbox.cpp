
#include <LearningEngine.h>

#include <glm/gtc/matrix_transform.hpp>

// TEMP:
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public LE::Layer
{
public:

	ExampleLayer()
		: LE::Layer("Layer"), m_Camera(-1.6f, 1.6f, -1.2f, 1.2f)
	{
		std::string vertexShader = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.f);
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
		
			in vec3 v_Position;
			in vec4 v_Color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_Shader.reset(LE::Shader::Create(vertexShader, fragmentShader));
		m_Shader->Bind();

		m_VertexArray.reset(LE::VertexArray::Create());

		float vb[7 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<LE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LE::VertexBuffer::Create(vb, sizeof(vb)));

		LE::VertexBufferLayout layout = {
			{ LE::ShaderDataType::Float3, "a_Position", false },
			{ LE::ShaderDataType::Float4, "a_Color", false }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t ib[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<LE::IndexBuffer> indexBuffer;
		indexBuffer.reset(LE::IndexBuffer::Create(ib, 6));
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}

	virtual void OnUpdate(LE::Timestep DeltaTime) override
	{
		float finalSpeed = m_CameraSpeed * DeltaTime;

		if (LE::Input::IsKeyPressed(LE_KEY_W))
			m_CameraPosition += glm::vec3(0, finalSpeed, 0);
		else if (LE::Input::IsKeyPressed(LE_KEY_S))
			m_CameraPosition += glm::vec3(0, -finalSpeed, 0);

		if (LE::Input::IsKeyPressed(LE_KEY_A))
			m_CameraPosition += glm::vec3(-finalSpeed, 0.f, 0);
		else if (LE::Input::IsKeyPressed(LE_KEY_D))
			m_CameraPosition += glm::vec3(finalSpeed, 0.f, 0);

		m_Camera.SetPosition(m_CameraPosition);

		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));
		LE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		LE::RenderCommand::Clear();

		LE::Renderer::BeginScene(m_Camera);

		std::dynamic_pointer_cast<LE::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int32_t i = 0; i < 20; i++)
		{
			for (int32_t j = 0; j < 20; j++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.f), glm::vec3(i * 0.11f, j * 0.11f, 0.f)) * scale;
				LE::Renderer::Submit(m_Shader, m_VertexArray, transform);
			}
		}

		LE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorPicker3("SquareColor", &m_SquareColor[0]);
		ImGui::End();
	}

	virtual void OnEvent(LE::Event& e) override
	{
		LE::EventDispatcher dispatcher(e);
	}

private:

	std::shared_ptr<LE::Shader> m_Shader;
	std::shared_ptr<LE::VertexArray> m_VertexArray;

	LE::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition = glm::vec3(0,0,0);
	float m_CameraSpeed = 1.f;

	glm::vec3 m_SquareColor = glm::vec3(0.2f, 0.2f, 0.8f);
};

class Sandbox : public LE::Application
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
};

LE::Application* LE::CreateApplication()
{
	return new Sandbox();
}