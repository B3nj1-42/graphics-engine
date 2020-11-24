#include "gepch.h"
#include "Application.h"

#include "GraphicsEngine/Events/ApplicationEvent.h"
#include "GraphicsEngine/Log.h"

namespace GraphicsEngine {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent windowEvent(1280, 720);
		if (windowEvent.IsInCategory(EventCategoryApplication))
		{
			GE_TRACE(windowEvent.ToString());
		}
		if (windowEvent.IsInCategory(EventCategoryInput))
		{
			GE_TRACE(windowEvent.ToString());
		}

		while (true)
		{
		}
	}

}