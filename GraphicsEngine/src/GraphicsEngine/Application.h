#pragma once

#include "Core.h"

#include "Window.h"
#include "GraphicsEngine/LayerStack.h"
#include "GraphicsEngine/Events/Event.h"
#include "GraphicsEngine/Events/ApplicationEvent.h"

#include "GraphicsEngine/Core/Timestep.h"

#include "GraphicsEngine/ImGui/ImGuiLayer.h"

namespace GraphicsEngine {

	class Application
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

	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
