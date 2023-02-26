#pragma once

#include "Yunni/Core.h"
#include "Yunni/Core/Timestep.h"
#include "Yunni/Events/Event.h"

namespace Yunni {
	class YUNNI_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
