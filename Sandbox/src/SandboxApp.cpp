#include <GraphicsEngine.h>

class Sandbox : public GraphicsEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

GraphicsEngine::Application* GraphicsEngine::CreateApplication()
{
	return new Sandbox();
}