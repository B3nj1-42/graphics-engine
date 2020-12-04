#include <GraphicsEngine.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public GraphicsEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(GraphicsEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			//	   x	 y	   z		  r	   g	 b	   a
			   -0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.9f, 1.0f,
				0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
				0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<GraphicsEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(GraphicsEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		GraphicsEngine::BufferLayout layout = {
			{ GraphicsEngine::ShaderDataType::Float3, "a_Position" },
			{ GraphicsEngine::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<GraphicsEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(GraphicsEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(GraphicsEngine::VertexArray::Create());

		float squareVertices[3 * 4] = {
			//	   x	 y	   z
			   -0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f,  0.5f, 0.0f,
			   -0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<GraphicsEngine::VertexBuffer> squareVB;
		squareVB.reset(GraphicsEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ GraphicsEngine::ShaderDataType::Float3, "a_Position" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<GraphicsEngine::IndexBuffer> squareIB;
		squareIB.reset(GraphicsEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
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
				color = v_Color;
			}

		)";

		m_Shader.reset(GraphicsEngine::Shader::Create(vertexSource, fragmentSource));

		std::string flatColorShaderVertexSource = R"(
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

		std::string flatColorShaderFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}

		)";

		m_FlatColorShader.reset(GraphicsEngine::Shader::Create(flatColorShaderVertexSource, flatColorShaderFragmentSource));
	}

	void OnUpdate(GraphicsEngine::Timestep ts) override
	{
		if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_UP) || GraphicsEngine::Input::IsKeyPressed(GE_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_DOWN) || GraphicsEngine::Input::IsKeyPressed(GE_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		
		if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_LEFT) || GraphicsEngine::Input::IsKeyPressed(GE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_RIGHT) || GraphicsEngine::Input::IsKeyPressed(GE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		
		if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (GraphicsEngine::Input::IsKeyPressed(GE_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;

		GraphicsEngine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		GraphicsEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		GraphicsEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<GraphicsEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<GraphicsEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f + m_SquarePosition.x, y * 0.11f + m_SquarePosition.y, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				GraphicsEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		GraphicsEngine::Renderer::Submit(m_Shader, m_VertexArray);

		GraphicsEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(GraphicsEngine::Event& event) override
	{
	}


private:
	std::shared_ptr<GraphicsEngine::Shader> m_Shader;
	std::shared_ptr<GraphicsEngine::VertexArray> m_VertexArray;

	std::shared_ptr<GraphicsEngine::Shader> m_FlatColorShader;
	std::shared_ptr<GraphicsEngine::VertexArray> m_SquareVA;

	GraphicsEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.5f;

	float m_CameraRotation;
	float m_CameraRotationSpeed = 90.0;
	
	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public GraphicsEngine::Application
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

GraphicsEngine::Application* GraphicsEngine::CreateApplication()
{
	return new Sandbox();
}