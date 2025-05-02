
#include "LEpch.h"

#include "Application.h"
#include "Input.h"

#include "LE/Renderer/Renderer.h"

#include "LE/Core/Timestep.h"

// TEMP:
#include <GLFW/glfw3.h>

namespace LE
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LE_CORE_ASSERT(!s_Instance, "Only one instance of Application can be present!");
		s_Instance = this;

		m_Window = TUniquePtr<Window>(Window::Create());
		m_Window->SetEventCallback(LE_BIND(this, &Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (bIsRunning)
		{
			// TODO: move glfw call to Platform::GetTime()
			float time = static_cast<float>(glfwGetTime());
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (m_Minimized == false)
			{
				for (Layer* currentLayer : m_LayerStack)
				{
					currentLayer->OnUpdate(timestep);
				}
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
		dispatcher.Dispatch<WindowCloseEvent>(LE_BIND(this, &Application::OnWindowCloseCallback));
		dispatcher.Dispatch<WindowResizeEvent>(LE_BIND(this, &Application::OnWindowResizeCallback));

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

	bool Application::OnWindowResizeCallback(const WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}