#include "ynpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Yunni {
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t  height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			YN_CORE_ASSERT(false, "RendererAPI::API::None is currently not support!");
			break;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		}

		YN_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch(Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			YN_CORE_ASSERT(false, "RendererAPI::API::None is currently not support!");
			break;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		}

		YN_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}
