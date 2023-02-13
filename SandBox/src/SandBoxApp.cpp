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
		if (Yunni::Input::IsKeyPressed(YN_KEY_TAB))
			YN_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Yunni::Event& event) override
	{
		if (event.GetEventType() == Yunni::EventType::KeyPressed)
		{
			Yunni::KeyPressedEvent& e = (Yunni::KeyPressedEvent&)event;
			if (e.GetKeyCode() == YN_KEY_TAB)
				YN_TRACE("Tab key is pressed (event)!");
			YN_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Yunni::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Yunni::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Yunni::Application* Yunni::CreateApplication()
{
	return new Sandbox();
}
