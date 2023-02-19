#pragma once

#include "Core.h"
#include "Window.h"
#include "Yunni/LayerStack.h"
#include "Yunni/Events/Event.h"
#include "Yunni/Events/ApplicationEvent.h"

#include "Yunni/ImGui/ImGuiLayer.h"
#include "Yunni/Renderer/Shader.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindoClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
 