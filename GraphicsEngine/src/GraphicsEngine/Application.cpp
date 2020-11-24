#include "gepch.h"
#include "Application.h"

#include "GraphicsEngine/Events/ApplicationEvent.h"

#include "GLFW/glfw3.h"

namespace GraphicsEngine {

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
			glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}