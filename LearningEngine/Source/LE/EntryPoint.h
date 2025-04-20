
#pragma once

#ifdef LE_PLATFORM_WINDOWS

extern LE::Application* LE::CreateApplication();

int main(int argc, char** argv)
{
	LE::Application* app = LE::CreateApplication();
	app->Run();
	delete app;
}

#endif
