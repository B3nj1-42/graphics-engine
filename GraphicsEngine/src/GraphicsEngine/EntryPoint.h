#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GraphicsEngine::Application* GraphicsEngine::CreateApplication();

int main(int argc, char** argv)
{
	GraphicsEngine::Log::Init();
	GE_CORE_WARN("initialized Core Log!");
	GE_INFO("initialized Cliet Log!");

	auto app = GraphicsEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif // GE_PLATFORM_WINDOWS
