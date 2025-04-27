
#pragma once

#include "Core.h"
#include "Window.h"
#include "LE/Events/ApplicationEvent.h"
#include "LayerStack.h"

#include "LE/ImGui/ImGuiLayer.h"

#include "LE/Renderer/OrthographicCamera.h"

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

		virtual void OnEvent(Event& e);

		void PushLayer(Layer* Layer);
		void PushOverlay(Layer* Overlay);

		inline Window& GetWindow() const
		{
			return *m_Window;
		}

	protected:

		virtual void Tick(float DeltaTime) { }

	private:

		bool OnWindowCloseCallback(const WindowCloseEvent& e);

	private:

		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool bIsRunning = true;

		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

