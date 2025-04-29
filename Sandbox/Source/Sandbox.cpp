
#include <LearningEngine.h>

class ExampleLayer : public LE::Layer
{
public:

	ExampleLayer()
		: LE::Layer("Layer"), m_Camera(-1.f, 1.f, -1.f, 1.f)
	{
		std::string vertexShader = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.f);
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

		m_Shader.reset(LE::Shader::Create(vertexShader, fragmentShader));
		m_Shader->Bind();

		m_VertexArray.reset(LE::VertexArray::Create());

		float vb[7 * 3] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<LE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LE::VertexBuffer::Create(vb, sizeof(vb)));

		LE::VertexBufferLayout layout = {
			{ LE::ShaderDataType::Float3, "a_Position", false },
			{ LE::ShaderDataType::Float4, "a_Color", false }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t ib[3] = { 0, 1, 2 };
		std::shared_ptr<LE::IndexBuffer> indexBuffer;
		indexBuffer.reset(LE::IndexBuffer::Create(ib, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}

	virtual void OnUpdate() override
	{
		LE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		LE::RenderCommand::Clear();

		LE::Renderer::BeginScene(m_Camera);

		LE::Renderer::Submit(m_Shader, m_VertexArray);

		LE::Renderer::EndScene();
	}

	bool OnKeyPressedEvent(LE::KeyPressedEvent& event)
	{
		switch (event.GetKeyCode())
		{
		case LE_KEY_W:
		{
			testPos += glm::vec3(0, -0.1f, 0);
			m_Camera.SetPosition(testPos);
			break;
		}
		case LE_KEY_S:
		{
			testPos += glm::vec3(0, 0.1f, 0);
			m_Camera.SetPosition(testPos);
			break;
		}
		case LE_KEY_D:
		{
			testPos += glm::vec3(-0.1f, 0.f, 0);
			m_Camera.SetPosition(testPos);
			break;
		}
		case LE_KEY_A:
		{
			testPos += glm::vec3(0.1f, -0.f, 0);
			m_Camera.SetPosition(testPos);
			break;
		}
		}

		return true;
	}

	virtual void OnEvent(LE::Event& e) override
	{
		LE::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<LE::KeyPressedEvent>(LE_BIND(this, &ExampleLayer::OnKeyPressedEvent));
	}

private:

	std::shared_ptr<LE::Shader> m_Shader;
	std::shared_ptr<LE::VertexArray> m_VertexArray;

	LE::OrthographicCamera m_Camera;

	glm::vec3 testPos = glm::vec3(0,0,0);
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