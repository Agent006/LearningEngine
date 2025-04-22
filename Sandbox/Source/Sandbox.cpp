
#include <LearningEngine.h>

class Sandbox : public LE::Application
{
public:

	Sandbox()
	{
		PushOverlay(new LE::ImGuiLayer());
	}
};

LE::Application* LE::CreateApplication()
{
	return new Sandbox();
}