#pragma once

#include  "Yunni/Renderer/RendererAPI.h"

namespace Yunni {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4 & color) override;

		virtual void SetViewport(int x, int y, uint32_t width, uint32_t height);

		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};
}
