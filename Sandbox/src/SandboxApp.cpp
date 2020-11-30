#include <GraphicsEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public GraphicsEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_TAB))
			GE_TRACE("Tab key is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		/*ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();*/
	}

	void OnEvent(GraphicsEngine::Event& event) override
	{
		if (event.GetEventType() == GraphicsEngine::EventType::KeyPressed)
		{
			GraphicsEngine::KeyPressedEvent& e = (GraphicsEngine::KeyPressedEvent&)event;
				GE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public GraphicsEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

GraphicsEngine::Application* GraphicsEngine::CreateApplication()
{
	return new Sandbox();
}