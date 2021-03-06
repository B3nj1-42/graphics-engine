#pragma once

#include "GraphicsEngine/Core.h"
#include "GraphicsEngine/Core/Timestep.h"
#include "GraphicsEngine/Events/Event.h"

namespace GraphicsEngine {

	class GRAPHICS_ENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}