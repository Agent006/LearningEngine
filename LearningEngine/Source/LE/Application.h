
#pragma once

#include "Core.h"
#include "Window.h"
#include "LE/Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace LE
{


	class LE_API Application
	{
	public:

		inline static Application& Get()
		{
			return *s_Instance;
		}

		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* Layer);
		void PushOverlay(Layer* Overlay);

		inline Window& GetWindow() const
		{
			return *m_Window;
		}

	private:

		bool OnWindowCloseCallback(const WindowCloseEvent& e);

	private:

		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		bool bIsRunning = true;

		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

