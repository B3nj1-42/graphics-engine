#pragma once

#include "Core.h"

#include "Window.h"
#include "GraphicsEngine/LayerStack.h"
#include "GraphicsEngine/Events/Event.h"
#include "GraphicsEngine/Events/ApplicationEvent.h"



namespace GraphicsEngine {

	class GRAPHICS_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClosed(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
