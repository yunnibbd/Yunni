#pragma once

#ifdef YN_PLATFORM_WINDOWS
	
extern Yunni::Application* Yunni::CreateApplication();

int main(int argc, char** argv)
{
	printf("Yunni Engine\n");
	auto app = Yunni::CreateApplication();
	app->Run();
	delete app;
}


#endif
