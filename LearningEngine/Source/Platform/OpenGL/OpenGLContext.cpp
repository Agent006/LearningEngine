
#include "LEpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LE
{
	OpenGLContext::OpenGLContext(GLFWwindow* NativeWindow)
		: m_NativeWindow(NativeWindow)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_NativeWindow);

		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LE_CORE_ASSERT(gladStatus, "Failed to initialize Glad!");

		LE_CORE_INFO("OpenGL Info:");
		LE_CORE_INFO("  OpenGL Rederer: {0}", (char*)glGetString(GL_VENDOR));
		LE_CORE_INFO("  OpenGL Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_NativeWindow);
	}
}