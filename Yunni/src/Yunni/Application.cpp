#include "ynpch.h"
#include "Application.h"
#include "Yunni/Log.h"
#include "Yunni/Events/ApplicationEvent.h"

namespace Yunni {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}
