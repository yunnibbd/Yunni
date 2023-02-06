#pragma once

#include "Core.h"

namespace Yunni {
	class YUNNI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
