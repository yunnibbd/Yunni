#pragma once

#include "Core.h"
#include "Window.h"
#include "Yunni/Events/ApplicationEvent.h"

namespace Yunni {
	class YUNNI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindoClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
