
#include "LEpch.h"
#include "WindowsInput.h"

#include "LE/Core/Application.h"

#include <GLFW/glfw3.h>

namespace LE
{
	TUniquePtr<Input> Input::s_Instance = MakeUnique<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int32_t Keycode) const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int keyResult = glfwGetKey(nativeWindow, Keycode);
		return keyResult == GLFW_PRESS || keyResult == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int32_t Button) const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int mouseButtonResult = glfwGetMouseButton(nativeWindow, Button);
		return mouseButtonResult == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMouseXYImpl() const
	{
		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(nativeWindow, &xpos, &ypos);

		return std::make_pair<float, float>((float)xpos, (float)ypos);
	}
}
