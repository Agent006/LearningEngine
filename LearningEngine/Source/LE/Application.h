
#pragma once

#include "Core.h"

namespace LE
{
	class LE_API Application
	{
	public:

		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

