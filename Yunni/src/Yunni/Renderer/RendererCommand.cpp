#include "ynpch.h"
#include "RendererCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Yunni {
	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI();
}
