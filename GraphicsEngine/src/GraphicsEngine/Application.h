#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "GraphicsEngine/Events/ApplicationEvent.h"

#include "Window.h"


namespace GraphicsEngine {

	class GRAPHICS_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

	private:
		bool OnWindowClosed(WindowCloseEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
