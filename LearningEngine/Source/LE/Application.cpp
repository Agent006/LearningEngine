
#include "LEpch.h"

#include "Application.h"

#include "Input.h"

#include <glad/glad.h>

#include "LE/Renderer/Shader.h"
#include "LE/Renderer/Buffers.h"

namespace LE
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
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
			
			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.f);
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
		
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		Shader testShader = Shader(vertexShader, fragmentShader);
		testShader.Bind();

		unsigned int vaIndex;
		glGenVertexArrays(1, &vaIndex);
		glBindVertexArray(vaIndex);

		float vb[3*3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.f,   0.5f, 0.0f
		};

		uint32_t ib[3] = { 0, 1, 2 };

		VertexBuffer* vertexBuffer = VertexBuffer::Create(vb, sizeof(vb));
		IndexBuffer* indexBuffer = IndexBuffer::Create(ib, 3);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		while (bIsRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* currentLayer : m_LayerStack)
			{
				currentLayer->OnUpdate();
			}

			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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