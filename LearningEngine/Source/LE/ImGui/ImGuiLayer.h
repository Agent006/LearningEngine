#pragma once

#include "LE/Layer.h"
#include "LE/Events/MouseEvent.h"
#include "LE/Events/ApplicationEvent.h"
#include "LE/Events/KeyEvent.h"

class GLFWwindow;

namespace LE
{
	class LE_API ImGuiLayer : public Layer
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;

	private:

		uint32_t KeyToImGuiKey(int Keycode, int Scancode);

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:

		float m_Time = 0.f;

	};
}