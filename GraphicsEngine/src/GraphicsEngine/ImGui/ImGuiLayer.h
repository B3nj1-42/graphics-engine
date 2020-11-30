#pragma once

#include "GraphicsEngine/Layer.h"

#include "GraphicsEngine/Events/ApplicationEvent.h"
#include "GraphicsEngine/Events/KeyEvent.h"
#include "GraphicsEngine/Events/MouseEvent.h"

namespace GraphicsEngine {

	class GRAPHICS_ENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}