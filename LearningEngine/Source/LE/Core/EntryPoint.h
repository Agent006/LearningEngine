
#pragma once

#include "LE/Core/Core.h"
#include "LE/Core/Log.h"

#ifdef LE_PLATFORM_WINDOWS

extern LE::Application* LE::CreateApplication();

int main(int argc, char** argv)
{
	LE::Log::Init();

	LE_PROFILE_BEGIN_SESSION("LEProfile-Startup.json");
	LE::Application* app = LE::CreateApplication();
	LE_PROFILE_END_SESSION();

	LE_PROFILE_BEGIN_SESSION("LEProfile-Runtime.json");
	app->Run();
	LE_PROFILE_END_SESSION();

	LE_PROFILE_BEGIN_SESSION("LEProfile-Shutdown.json");
	delete app;
	LE_PROFILE_END_SESSION();
}

#endif
