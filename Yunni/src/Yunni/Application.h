#pragma once

#include "Core.h"
#include "Window.h"
#include "Yunni/LayerStack.h"
#include "Yunni/Events/Event.h"
#include "Yunni/Events/ApplicationEvent.h"

namespace Yunni {
	class YUNNI_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* overlay);

	private:
		bool OnWindoClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
