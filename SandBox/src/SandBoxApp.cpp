#include <Yunni.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Yunni::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Yunni::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Yunni::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Yunni::VertexBuffer::Create(vertices, sizeof(vertices)));

		Yunni::BufferLayout layout = {
			{ Yunni::ShaderDataType::Float3, "a_Position" },
			{ Yunni::ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Yunni::IndexBuffer> indexBuffer;
		indexBuffer.reset(Yunni::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Yunni::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<Yunni::VertexBuffer> squareVB;
		squareVB.reset(Yunni::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Yunni::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Yunni::IndexBuffer> squareIB;
		squareIB.reset(Yunni::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;			

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				//color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Yunni::Shader::Create(vertexSource, fragmentSource));

		std::string flatShaderVertexSource = R"(
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

		std::string flatShaderFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;			

			in vec3 v_Position;
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Yunni::Shader::Create(flatShaderVertexSource, flatShaderFragmentSource));
	}

	void OnUpdate(Yunni::Timestep ts) override
	{
		YN_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
		float  time = ts;
		if (Yunni::Input::IsKeyPressed(YN_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Yunni::Input::IsKeyPressed(YN_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Yunni::Input::IsKeyPressed(YN_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Yunni::Input::IsKeyPressed(YN_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Yunni::Input::IsKeyPressed(YN_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		if (Yunni::Input::IsKeyPressed(YN_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Yunni::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Yunni::RendererCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Yunni::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Yunni::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Yunni::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SqareColor);

		for (int y = 0; y < 20; ++y) 
		{
			for (int x = 0; x < 20; ++x) 
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Yunni::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		
		Yunni::Renderer::Submit(m_Shader, m_VertexArray);

		Yunni::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SqareColor));
		ImGui::End();
	}

	void OnEvent(Yunni::Event& event) override
	{
	}

private:
	std::shared_ptr<Yunni::Shader> m_Shader;
	std::shared_ptr<Yunni::VertexArray> m_VertexArray;

	std::shared_ptr<Yunni::Shader> m_FlatColorShader;
	std::shared_ptr<Yunni::VertexArray> m_SquareVA;

	Yunni::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SqareColor = { 0.2f, 0.3f, 0.8f };
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
