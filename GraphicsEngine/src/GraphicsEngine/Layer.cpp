#include "gepch.h"
#include "Layer.h"

namespace GraphicsEngine {

	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	Layer::~Layer() {}
}