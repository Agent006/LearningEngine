
#pragma once

#include "LE/Core/Core.h"
#include "LE/Core/Layer.h"

namespace LE
{
	class LayerStack
	{
	public:

		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* Layer); 
		void PushOverlay(Layer* Overlay);
		void PopLayer(Layer* Layer);
		void PopOverlay(Layer* Overlay);

		std::vector<Layer*>::iterator begin()
		{
			return m_Layers.begin();
		}

		std::vector<Layer*>::iterator end()
		{
			return m_Layers.end();
		}

	private:

		std::vector<Layer*> m_Layers;
		uint32_t m_LayerInsertIndex = 0;
	};
}