#pragma once

#include "Yunni/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Yunni {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}
