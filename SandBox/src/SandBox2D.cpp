#include <ynpch.h>
#include "SandBox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_Texture = Yunni::Texture2D::Create("assets/textures/mps4.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Yunni::Timestep ts)
{
	YN_PROFILE_FUNCTION();

	//Update
	{
		YN_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	//Render
	{
		YN_PROFILE_SCOPE("Render Pre");
		Yunni::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Yunni::RendererCommand::Clear();
	}

	{
		YN_PROFILE_SCOPE("Render Draw");
		Yunni::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Yunni::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Yunni::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Yunni::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);
		Yunni::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	for(auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Yunni::Event& e)
{
	m_CameraController.OnEvent(e);
}
