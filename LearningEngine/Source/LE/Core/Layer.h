
#pragma once

#include "LE/Core/Core.h"
#include "LE/Events/Event.h"
#include "LE/Core/Timestep.h"

namespace LE
{
	class Layer
	{
	public:

		Layer(const std::string& LayerName = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep DeltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const
		{
			return m_DebugName;
		}

	protected:

		std::string m_DebugName;
	};
}