#pragma once

#ifdef YN_PLATFORM_WINDOWS
	
extern Yunni::Application* Yunni::CreateApplication();

int main(int argc, char** argv)
{
	Yunni::Log::Init();
	YN_CORE_WARN("Initialized Log!");
	int a = 5;
	YN_INFO("Hello! Var={0}", a);

	auto app = Yunni::CreateApplication();
	app->Run();
	delete app;
}

#endif
