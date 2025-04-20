
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

		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher = EventDispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowCloseCallback, this, std::placeholders::_1));
	}

	bool Application::OnWindowCloseCallback(const WindowCloseEvent & e)
	{
		bIsRunning = false;
		return true;
	}
}