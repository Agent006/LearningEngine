
#include "LEpch.h"
#include "LayerStack.h"

namespace LE
{
	LayerStack::~LayerStack()
	{
		for (Layer* currentLayer : m_Layers)
		{
			currentLayer->OnDetach();
			delete currentLayer;
		}
	}

	void LayerStack::PushLayer(Layer* Layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, Layer);
		m_LayerInsertIndex++;
		Layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* Overlay)
	{
		m_Layers.emplace_back(Overlay);
		Overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* Layer)
	{
		auto it = std::find(begin(), end() + m_LayerInsertIndex, Layer);

		if (it != end())
		{
			Layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* Overlay)
	{
		auto it = std::find(begin() + m_LayerInsertIndex, end(), Overlay);

		if (it != end())
		{
			Overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}