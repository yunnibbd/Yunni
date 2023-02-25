#pragma once

#include "Core.h"
#include "Window.h"
#include "Yunni/LayerStack.h"
#include "Yunni/Events/Event.h"
#include "Yunni/Events/ApplicationEvent.h"

#include "Yunni/ImGui/ImGuiLayer.h"

#include "Yunni/Renderer/Shader.h"
#include "Yunni/Renderer/Buffer.h"
#include "Yunni/Renderer/VertexArray.h"
#include "Yunni/Renderer/OrthographicCamera.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
 