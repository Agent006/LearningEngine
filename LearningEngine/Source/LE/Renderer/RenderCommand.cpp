#include "LEpch.h"
#include "RenderCommand.h"

namespace LE
{
	TUniquePtr<RendererAPI> RenderCommand::s_RenderAPI = RendererAPI::Create();
}