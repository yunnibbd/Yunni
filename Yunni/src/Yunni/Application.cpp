#include "Application.h"
#include "Yunni/Log.h"
#include "Yunni/Events/ApplicationEvent.h"

namespace Yunni {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			YN_TRACE(e);
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			YN_TRACE(e);
		}

		while (true);
	}
}
