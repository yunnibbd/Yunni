#pragma once

#include "Yunni/Core/Layer.h"

#include "Yunni/Events/ApplicationEvent.h"
#include "Yunni/Events/KeyEvent.h"
#include "Yunni/Events/MouseEvent.h"

namespace Yunni {

	class YUNNI_API ImGuiLayer : public Layer
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