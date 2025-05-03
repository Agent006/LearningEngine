#include "LEpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LE
{
	TUniquePtr<RendererAPI> RenderCommand::s_RenderAPI = MakeUnique<OpenGLRendererAPI>();
}