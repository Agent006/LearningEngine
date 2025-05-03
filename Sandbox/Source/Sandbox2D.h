#pragma once

#include <LearningEngine.h>

class Sandbox2D : public LE::Layer
{
public:

	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(LE::Timestep DeltaTime) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(LE::Event& e) override;

private:

	LE::TSharedPtr<LE::VertexArray> m_VertexArray;
	LE::TSharedPtr<LE::Shader> m_Shader;

	LE::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor = glm::vec4(0.2f, 0.2f, 0.8f, 1.f);
};