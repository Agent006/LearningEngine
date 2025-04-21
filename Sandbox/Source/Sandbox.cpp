
#include <LearningEngine.h>

class ExampleLayer : public LE::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		LE_TRACE("Update");
	}

	void OnEvent(LE::Event& e) override
	{
		LE_TRACE("{0}", e.ToString());
	}
};

class Sandbox : public LE::Application
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
};

LE::Application* LE::CreateApplication()
{
	return new Sandbox();
}