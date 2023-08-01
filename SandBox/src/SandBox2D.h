#pragma once

#include "Yunni.h"

class Sandbox2D : public Yunni::Layer
{
public:
	Sandbox2D();

	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Yunni::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Yunni::Event& e) override;
	
private:
	Yunni::OrthographicCameraController m_CameraController;
	
	//Temp
	Yunni::Ref<Yunni::Shader> m_FlatColorShader;
	Yunni::Ref<Yunni::Texture2D> m_Texture;
	Yunni::Ref<Yunni::VertexArray> m_SquareVA;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
