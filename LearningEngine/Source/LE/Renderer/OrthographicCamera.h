#pragma once

#include <glm/glm.hpp>

namespace LE
{
	class OrthographicCamera
	{
	public:

		OrthographicCamera(float Left, float Right, float Bottom, float Top);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& Position);

		inline float GetRotation() const { return m_Rotation; }
		void SetRotation(float Rotation);

		inline const glm::mat4& GetProjectionMatrix()		const	{ return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix()				const	{ return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix()	const	{ return m_ViewProjectionMatrix; }

	private:

		void RecalculateViewMatrix();

	private:

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.f, 0.f, 0.f };
		float m_Rotation = 0.f;
	};
}