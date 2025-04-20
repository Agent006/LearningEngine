
#pragma once

#include "Core.h"
#include "Window.h"
#include "LE/Events/ApplicationEvent.h"

namespace LE
{
	class LE_API Application
	{
	public:

		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:

		bool OnWindowCloseCallback(const WindowCloseEvent& e);

	private:

		std::unique_ptr<Window> m_Window;
		bool bIsRunning = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

