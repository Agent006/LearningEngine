
#pragma once

#include "Core.h"
#include "Window.h"
#include "LE/Events/ApplicationEvent.h"
#include "LayerStack.h"

#include "LE/ImGui/ImGuiLayer.h"

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

		TUniquePtr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool bIsRunning = true;

		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.f;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

