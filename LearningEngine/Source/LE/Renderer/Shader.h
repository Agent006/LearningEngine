#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace LE
{
	class Shader
	{
	public:

		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& Name, int32_t Value) = 0;
		virtual void SetFloat3(const std::string& Name, const glm::vec3& Value) = 0;
		virtual void SetFloat4(const std::string& Name, const glm::vec4& Value) = 0;
		virtual void SetMat4(const std::string& Name, const glm::mat4& Value) = 0;

		virtual const std::string& GetName() const = 0;

		static TSharedPtr<Shader> Create(const std::string& FilePath);
		static TSharedPtr<Shader> Create(const std::string& Name, const std::string& VertexShader, const std::string& FragmentShader);
	};

	class ShaderLibrary
	{
	public:

		void Add(const TSharedPtr<Shader>& Shader);
		TSharedPtr<Shader> Load(const std::string& FilePath);

		TSharedPtr<Shader> Get(const std::string& Name);

		bool Exists(const std::string& Name) const;

	private:

		std::unordered_map<std::string, TSharedPtr<Shader>> m_Shaders;
	};
}