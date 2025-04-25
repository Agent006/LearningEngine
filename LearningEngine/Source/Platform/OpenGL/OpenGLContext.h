#pragma once

#include "LE/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace LE
{
	class OpenGLContext : public GraphicsContext
	{
	public:

		OpenGLContext(GLFWwindow* NativeWindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* m_NativeWindow;
	};
}