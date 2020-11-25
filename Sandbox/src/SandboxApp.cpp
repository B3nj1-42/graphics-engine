#include <GraphicsEngine.h>

class ExampleLayer : public GraphicsEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		GE_INFO("ExampleLayer::Update");
	}

	void OnEvent(GraphicsEngine::Event& event) override
	{
		GE_TRACE("{0}", event.ToString());
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