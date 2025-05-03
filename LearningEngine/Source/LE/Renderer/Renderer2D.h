#pragma once

#include "LE/Renderer/OrthographicCamera.h"
#include "LE/Renderer/Texture.h"

namespace LE
{
	class Renderer2D
	{
	protected:

		Renderer2D() = default;

	public:

		Renderer2D(const Renderer2D&) = delete;
		Renderer2D& operator=(const Renderer2D&) = delete;

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& Camera);
		static void EndScene();

		// Primitives

		static void DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& Color);
		static void DrawQuad(const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& Color);
		static void DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const TSharedPtr<Texture2D>& Texture);
		static void DrawQuad(const glm::vec3& Position, const glm::vec2& Size, const TSharedPtr<Texture2D>& Texture);
	};
}