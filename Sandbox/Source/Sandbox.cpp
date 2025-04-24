
#include <LearningEngine.h>

class Sandbox : public LE::Application
{
public:

	Sandbox()
	{
	}
};

LE::Application* LE::CreateApplication()
{
	return new Sandbox();
}