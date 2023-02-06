#include <Yunni.h>

class Sandbox : public Yunni::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Yunni::Application* Yunni::CreateApplication()
{
	return new Sandbox();
}
