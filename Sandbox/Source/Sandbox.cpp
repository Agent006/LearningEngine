
#include <LearningEngine.h>

class Sandbox : public LE::Application
{

};

LE::Application* LE::CreateApplication()
{
	return new Sandbox();
}