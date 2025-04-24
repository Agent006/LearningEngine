
#pragma once

#include "LE/Core.h"
#include "LE/Events/Event.h"

namespace LE
{
	class LE_API Layer
	{
	public:

		Layer(const std::string& LayerName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
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