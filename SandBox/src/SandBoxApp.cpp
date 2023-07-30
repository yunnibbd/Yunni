#include <Yunni.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Yunni::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray.reset(Yunni::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Yunni::Ref<Yunni::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Yunni::VertexBuffer::Create(vertices, sizeof(vertices)));

		Yunni::BufferLayout layout = {
			{ Yunni::ShaderDataType::Float3, "a_Position" },
			{ Yunni::ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Yunni::Ref<Yunni::IndexBuffer> indexBuffer;
		indexBuffer.reset(Yunni::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Yunni::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Yunni::Ref<Yunni::VertexBuffer> squareVB;
		squareVB.reset(Yunni::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Yunni::ShaderDataType::Float3, "a_Position" },
			{ Yunni::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Yunni::Ref<Yunni::IndexBuffer> squareIB;
		squareIB.reset(Yunni::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";
		
		m_FlatColorShader = Yunni::Shader::Create("VertexPosColor", vertexSource, fragmentSource);

		const auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Yunni::Texture2D::Create("assets/textures/mps4.png");
		m_LogoTexture = Yunni::Texture2D::Create("assets/textures/logo.png");

		std::dynamic_pointer_cast<Yunni::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Yunni::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Yunni::Timestep ts) override
	{
		//Update
		m_CameraController.OnUpdate(ts);

		//Render
		Yunni::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Yunni::RendererCommand::Clear();

		Yunni::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Yunni::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Yunni::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; ++y) 
		{
			for (int x = 0; x < 20; ++x) 
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Yunni::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		const auto textureShader = m_ShaderLibrary.Get("Texture.glsl");

		m_Texture->Bind();
		Yunni::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_LogoTexture->Bind();
		Yunni::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Triangle
		//Yunni::Renderer::Submit(m_Shader, m_VertexArray);

		Yunni::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Yunni::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Yunni::ShaderLibrary m_ShaderLibrary;
	Yunni::Ref<Yunni::Shader> m_FlatColorShader;
	Yunni::Ref<Yunni::VertexArray> m_VertexArray;

	Yunni::Ref<Yunni::VertexArray> m_SquareVA;

	Yunni::Ref<Yunni::Texture2D> m_Texture, m_LogoTexture;

	Yunni::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Yunni::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Yunni::Application* Yunni::CreateApplication()
{
	return new Sandbox();
}
