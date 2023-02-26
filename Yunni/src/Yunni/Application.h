#pragma once

#include "Core.h"
#include "Window.h"
#include "Yunni/LayerStack.h"
#include "Yunni/Events/Event.h"
#include "Yunni/Events/ApplicationEvent.h"

#include "Yunni/ImGui/ImGuiLayer.h"

namespace Yunni {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindoClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
 