
#include "LEpch.h"

#include "Application.h"


namespace LE
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (bIsRunning)
		{
			m_Window->OnUpdate();

			for (Layer* currentLayer : m_LayerStack)
			{
				currentLayer->OnUpdate();
			}

		}
	}

	void Application::PushLayer(Layer* Layer)
	{
		m_LayerStack.PushLayer(Layer);
	}

	void Application::PushOverlay(Layer* Overlay)
	{
		m_LayerStack.PushOverlay(Overlay);
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