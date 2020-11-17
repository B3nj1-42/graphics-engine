#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GraphicsEngine::Application* GraphicsEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = GraphicsEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif // GE_PLATFORM_WINDOWS
