
#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.f)
{
}

void Sandbox2D::OnAttach()
{
	LE_PROFILE_FUNCTION();

	m_Texture = LE::Texture2D::Create("Assets/Textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	LE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(LE::Timestep DeltaTime)
{
	LE_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(DeltaTime);

	LE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
	LE::RenderCommand::Clear();

	LE::Renderer2D::BeginScene(m_CameraController.GetCamera());
	LE::Renderer2D::DrawQuad(glm::vec3(0.f, 0.f, 1.f), glm::vec2(1.f, 1.f), glm::vec4(1.f, 0.f, 0.f, 1.f));
	LE::Renderer2D::DrawQuad(glm::vec3(-0.5f, -0.5f, 1.f), glm::vec2(0.5f, 0.5f), glm::vec4(0.8f, 1.f, 0.2f, 1.f));
	LE::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, 0.1f), glm::vec2(10.f, 10.f), m_Texture);
	LE::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	LE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorPicker4("SquareColor", &m_SquareColor[0]);
	ImGui::End();
}

void Sandbox2D::OnEvent(LE::Event& e)
{
	LE::EventDispatcher dispatcher(e);
	m_CameraController.OnEvent(e);
}