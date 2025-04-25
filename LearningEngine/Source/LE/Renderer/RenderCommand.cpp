#include "LEpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LE
{
	RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRendererAPI();
}