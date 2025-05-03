
#pragma once

#include "LE/Core/Core.h"
#include "LE/Core/Log.h"

#ifdef LE_PLATFORM_WINDOWS

extern LE::Application* LE::CreateApplication();

int main(int argc, char** argv)
{
	LE::Log::Init();
	LE_CORE_WARN("Initialized Log!");
	LE_INFO("Hello world!");

	LE::Application* app = LE::CreateApplication();
	app->Run();
	delete app;
}

#endif
