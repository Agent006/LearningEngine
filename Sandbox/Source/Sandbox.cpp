
#include <LearningEngine.h>
#include <LE/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "LE/Events/ApplicationEvent.h"

#include <glm/gtc/matrix_transform.hpp>

// TEMP:
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public LE::Layer
{
public:

	ExampleLayer()
		: LE::Layer("Layer"), m_CameraController(1280.f / 720.f)
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

		m_Shader = LE::Shader::Create("ShaderName", vertexShader, fragmentShader);
		LE::TSharedPtr<LE::Shader> textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

		std::dynamic_pointer_cast<LE::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

		m_Texture = LE::Texture2D::Create("Assets/Textures/Checkerboard.png");
		m_ChernoLogoTexture = LE::Texture2D::Create("Assets/Textures/ChernoLogo.png");
		std::dynamic_pointer_cast<LE::OpenGLShader>(textureShader)->Bind();

		m_VertexArray = LE::VertexArray::Create();

		float vb[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		LE::TSharedPtr<LE::VertexBuffer> vertexBuffer;
		vertexBuffer = LE::VertexBuffer::Create(vb, sizeof(vb));

		LE::VertexBufferLayout layout = {
			{ LE::ShaderDataType::Float3, "a_Position", false },
			{ LE::ShaderDataType::Float2, "a_TexCoord", false }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t ib[6] = { 0, 1, 2, 2, 3, 0 };
		LE::TSharedPtr<LE::IndexBuffer> indexBuffer;
		indexBuffer = LE::IndexBuffer::Create(ib, 6);
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}

	virtual void OnUpdate(LE::Timestep DeltaTime) override
	{
		m_CameraController.OnUpdate(DeltaTime);

		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));
		LE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		LE::RenderCommand::Clear();

		LE::Renderer::BeginScene(m_CameraController.GetCamera());

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

		LE::TSharedPtr<LE::Shader> textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind(0);
		LE::Renderer::Submit(textureShader, m_VertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind(0);
		LE::Renderer::Submit(textureShader, m_VertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

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
		m_CameraController.OnEvent(e);
	}

private:

	LE::ShaderLibrary m_ShaderLibrary;

	LE::TSharedPtr<LE::Shader> m_Shader;
	LE::TSharedPtr<LE::Texture> m_Texture, m_ChernoLogoTexture;
	LE::TSharedPtr<LE::VertexArray> m_VertexArray;

	LE::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = glm::vec3(0.2f, 0.2f, 0.8f);
};

class Sandbox : public LE::Application
{
public:

	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
};

LE::Application* LE::CreateApplication()
{
	return new Sandbox();
}