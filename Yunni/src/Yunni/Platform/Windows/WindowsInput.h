#pragma once

#include "Yunni/Input.h"

namespace Yunni {
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button);
		virtual std::pair<float, float> GetMousePositionImpl() ;
		virtual float GetMouseXImpl();
		virtual float GetMouseYImpl();
	};
}
