#include "gepch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GraphicsEngine {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI: {0}", Renderer::GetAPI());
		return nullptr;
	}
}