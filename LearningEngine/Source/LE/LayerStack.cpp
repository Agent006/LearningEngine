
#include "LEpch.h"
#include "LayerStack.h"

namespace LE
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* currentLayer : m_Layers)
		{
			delete currentLayer;
		}
	}

	void LayerStack::PushLayer(Layer* Layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, Layer);
	}

	void LayerStack::PushOverlay(Layer* Overlay)
	{
		m_Layers.emplace_back(Overlay);
	}

	void LayerStack::PopLayer(Layer* Layer)
	{
		auto it = std::find(begin(), end(), Layer);

		if (it != end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* Overlay)
	{
		auto it = std::find(begin(), end(), Overlay);

		if (it != end())
		{
			m_Layers.erase(it);
		}
	}
}