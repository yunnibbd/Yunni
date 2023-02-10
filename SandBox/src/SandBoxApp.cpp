#include <Yunni.h>

class ExampleLayer : public Yunni::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		YN_INFO("ExampleLayer::Update");
	}

	void OnEvent(Yunni::Event& event) override
	{
		YN_TRACE("{0}", event);
	}
};

class Sandbox : public Yunni::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Yunni::Application* Yunni::CreateApplication()
{
	return new Sandbox();
}
