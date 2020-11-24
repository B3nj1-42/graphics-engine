#pragma once

#include "Core.h"
#include <GraphicsEngine\Window.h>


namespace GraphicsEngine {

	class GRAPHICS_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
