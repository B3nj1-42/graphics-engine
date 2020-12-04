#include "gepch.h"
#include "Shader.h"

#include "gepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GraphicsEngine {

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSource, fragmentSource);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI: {0}", Renderer::GetAPI());
		return nullptr;
	}
}