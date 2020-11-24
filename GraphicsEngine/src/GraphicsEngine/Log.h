#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace GraphicsEngine {

	class GRAPHICS_ENGINE_API Log
	{
	public:
		static void Init();
	
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define GE_CORE_TRACE(...)    ::GraphicsEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)     ::GraphicsEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...)     ::GraphicsEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...)    ::GraphicsEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_CRITICAL(...) ::GraphicsEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GE_TRACE(...)	 	  ::GraphicsEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...)          ::GraphicsEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...)          ::GraphicsEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...)         ::GraphicsEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define GE_CRITICAL(...)      ::GraphicsEngine::Log::GetClientLogger()->critical(__VA_ARGS__)