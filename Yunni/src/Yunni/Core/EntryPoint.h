#pragma once

#ifdef YN_PLATFORM_WINDOWS
	
extern Yunni::Application* Yunni::CreateApplication();

int main(int argc, char** argv)
{
	Yunni::Log::Init();

	YN_PROFILE_BEGIN_SESSION("Startup", "YunniProfile-Startip.json");
	auto app = Yunni::CreateApplication();
	YN_PROFILE_END_SESSION();

	YN_PROFILE_BEGIN_SESSION("Runtime", "YunniProfile-Runtime.json");
	app->Run();
	YN_PROFILE_END_SESSION();

	YN_PROFILE_BEGIN_SESSION("Shutdown", "YunniProfile-Shutdown.json");
	delete app;
	YN_PROFILE_END_SESSION();
}

#endif
