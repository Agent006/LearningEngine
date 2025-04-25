#include "LEpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace LE
{
	OrthographicCamera::OrthographicCamera(float Left, float Right, float Bottom, float Top)
		: m_ProjectionMatrix(glm::ortho(Left, Right, Bottom, Top, -1.f, 1.f)), m_ViewMatrix(1.f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& Position)
	{ 
		m_Position = Position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float Rotation)
	{
		m_Rotation = Rotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position) * 
			glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation), glm::vec3(0.f, 0.f, 1.f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}