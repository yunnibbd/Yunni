#include "ynpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Yunni {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		YN_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		YN_CORE_ASSERT(status, "Failed to initialize Glad!");

		YN_CORE_INFO("OpenGL Info:");
		YN_CORE_INFO(" Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		YN_CORE_INFO(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		YN_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
