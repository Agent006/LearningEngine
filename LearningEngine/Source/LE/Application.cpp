
#include "LEpch.h"

#include "Application.h"

#include "Input.h"

#include "LE/Renderer/Renderer.h"
#include "LE/Renderer/Shader.h"
#include "LE/Renderer/Buffers.h"
#include "LE/Renderer/VertexArray.h"
#include "LE/Renderer/VertexBufferLayout.h"

namespace LE
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		: Camera(-1.f, 1.f, -1.f, 1.f)
	{
		LE_CORE_ASSERT(!s_Instance, "Only one instance of Application can be present!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LE_BIND(this, &Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::Run()
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

		std::shared_ptr<Shader> testShader;
		testShader.reset(Shader::Create(vertexShader, fragmentShader));
		testShader->Bind();

		std::shared_ptr<VertexArray> vertexArray;
		vertexArray.reset(VertexArray::Create());

		float vb[7*3] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};
		
		std::shared_ptr<VertexBuffer> vertexBuffer; 
		vertexBuffer.reset(VertexBuffer::Create(vb, sizeof(vb)));

		VertexBufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position", false },			
			{ ShaderDataType::Float4, "a_Color", false }
		};

		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t ib[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(ib, 3));
		vertexArray->SetIndexBuffer(indexBuffer);

		while (bIsRunning)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
			RenderCommand::Clear();

			Renderer::BeginScene(Camera);

			Renderer::Submit(testShader, vertexArray);

			Renderer::EndScene();

			for (Layer* currentLayer : m_LayerStack)
			{
				currentLayer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* currentLayer : m_LayerStack)
			{
				currentLayer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* Layer)
	{
		m_LayerStack.PushLayer(Layer);
		Layer->OnAttach();
	}

	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
		Overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher = EventDispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowCloseCallback, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
			{
				break;
			}
		}
	}

	bool Application::OnWindowCloseCallback(const WindowCloseEvent & e)
	{
		bIsRunning = false;
		return true;
	}
}