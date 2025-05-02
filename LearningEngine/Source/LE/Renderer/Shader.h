#pragma once

#include <string>
#include <unordered_map>

namespace LE
{
	class Shader
	{
	public:

		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

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