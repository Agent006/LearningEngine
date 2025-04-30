
#include <LearningEngine.h>

#include <glm/gtc/matrix_transform.hpp>

// TEMP:
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public LE::Layer
{
public:

	ExampleLayer()
		: LE::Layer("Layer"), m_Camera(-2.56f, 2.56f, -1.44f, 1.44f)
	{
		std::string vertexShader = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.f);
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
		
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_Shader.reset(LE::Shader::Create(vertexShader, fragmentShader));
		m_TextureShader.reset(LE::Shader::Create("Assets/Shaders/Texture.glsl"));

		std::dynamic_pointer_cast<LE::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

		m_Texture = LE::Texture2D::Create("Assets/Textures/Checkerboard.png");
		m_ChernoLogoTexture = LE::Texture2D::Create("Assets/Textures/ChernoLogo.png");
		std::dynamic_pointer_cast<LE::OpenGLShader>(m_TextureShader)->Bind();

		m_VertexArray.reset(LE::VertexArray::Create());

		float vb[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		LE::TSharedPtr<LE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LE::VertexBuffer::Create(vb, sizeof(vb)));

		LE::VertexBufferLayout layout = {
			{ LE::ShaderDataType::Float3, "a_Position", false },
			{ LE::ShaderDataType::Float2, "a_TexCoord", false }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t ib[6] = { 0, 1, 2, 2, 3, 0 };
		LE::TSharedPtr<LE::IndexBuffer> indexBuffer;
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

		std::dynamic_pointer_cast<LE::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<LE::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int32_t i = 0; i < 20; i++)
		{
			for (int32_t j = 0; j < 20; j++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.f), glm::vec3(i * 0.11f, j * 0.11f, 0.f)) * scale;
				LE::Renderer::Submit(m_Shader, m_VertexArray, transform);
			}
		}

		m_Texture->Bind(0);
		LE::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind(0);
		LE::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

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

	LE::TSharedPtr<LE::Shader> m_Shader, m_TextureShader;
	LE::TSharedPtr<LE::Texture> m_Texture, m_ChernoLogoTexture;
	LE::TSharedPtr<LE::VertexArray> m_VertexArray;

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