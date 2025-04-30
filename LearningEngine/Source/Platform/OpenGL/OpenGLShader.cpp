#include "LEpch.h"
#include "OpenGLShader.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace LE
{
	static GLenum ShaderTypeFromString(const std::string& TypeStr)
	{
		if (TypeStr == "vertex")
			return GL_VERTEX_SHADER;
		else if (TypeStr == "fragment" || TypeStr == "pixel")
			return GL_FRAGMENT_SHADER;

		LE_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& FilePath)
	{
		std::string fileStr = ReadFile(FilePath);
		std::unordered_map<GLenum, std::string> shaderSrc = PreProcess(fileStr);
		Compile(shaderSrc);
	}

	OpenGLShader::OpenGLShader(const std::string& VertexShader, const std::string& FragmentShader)
	{
		std::unordered_map<GLenum, std::string> shaderSrc;
		shaderSrc.insert({ GL_VERTEX_SHADER, VertexShader });
		shaderSrc.insert({ GL_FRAGMENT_SHADER, FragmentShader });

		Compile(shaderSrc);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

	std::string OpenGLShader::ReadFile(const std::string& FilePath) const
	{
		std::string result;

		std::ifstream in(FilePath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			LE_CORE_ERROR("Could not open shader file \"{0}\"!", FilePath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& Source)
	{
		std::unordered_map<GLenum, std::string> shaderSrc;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = Source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = Source.find_first_of("\r\n", pos);
			LE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = Source.substr(begin, eol - begin);
			LE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = Source.find_first_not_of("\r\n", eol);
			pos = Source.find(typeToken, nextLinePos);
			shaderSrc[ShaderTypeFromString(type)] = Source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? Source.size() - 1 : nextLinePos));
		}

		return shaderSrc;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSrc)
	{
		uint32_t programId = glCreateProgram();
		std::vector<uint32_t> shaderIds;
		shaderIds.reserve(ShaderSrc.size());

		for (const std::pair<GLenum, std::string>& currentShaderSrc : ShaderSrc)
		{
			const GLenum type = currentShaderSrc.first;
			const std::string& sourceStr = currentShaderSrc.second;

			uint32_t shaderId = glCreateShader(type);
			shaderIds.push_back(shaderId);

			const char* source = sourceStr.c_str();
			glShaderSource(shaderId, 1, &source, 0);

			glCompileShader(shaderId);

			int32_t isCompiled = 0;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				for (uint32_t currentShaderId : shaderIds)
				{
					glDeleteShader(currentShaderId);
				}

				int32_t maxLength = 0;
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
				if (maxLength > 0)
				{
					std::vector<char> infoLog(maxLength);
					glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

					LE_CORE_ERROR("{0}", infoLog.data());
				}

				LE_CORE_ASSERT(false, "Shader compilation failure!");

				break;
			}

			glAttachShader(programId, shaderId);
		}

		glLinkProgram(programId);

		int32_t isLinked = 0;
		glGetProgramiv(programId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			for (uint32_t currentShaderId : shaderIds)
			{
				glDeleteShader(currentShaderId);
			}

			int32_t maxLength = 0;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
			if (maxLength > 0)
			{
				std::vector<char> infoLog(maxLength);
				glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);

				LE_CORE_ERROR("{0}", infoLog.data());
			}

			glDeleteProgram(programId);

			LE_CORE_ASSERT(false, "Shader linking failure!");

			return;
		}

		for (uint32_t currentShaderId : shaderIds)
		{
			glDetachShader(programId, currentShaderId);
		}

		m_RendererId = programId;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& Name, int32_t Integer) const
	{
		int32_t pos = glGetUniformLocation(m_RendererId, Name.c_str());
		glUniform1i(pos, Integer);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& Name, float Value) const
	{
		int32_t pos = glGetUniformLocation(m_RendererId, Name.c_str());
		glUniform1f(pos, Value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& Name, const glm::vec2& Value) const
	{
		int32_t pos = glGetUniformLocation(m_RendererId, Name.c_str());
		glUniform2f(pos, Value.x,  Value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& Name, const glm::vec3& Value) const
	{
		int32_t pos = glGetUniformLocation(m_RendererId, Name.c_str());
		glUniform3f(pos, Value.x, Value.y, Value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& Name, const glm::vec4& Value) const
	{
		int32_t pos = glGetUniformLocation(m_RendererId, Name.c_str());
		glUniform4f(pos, Value.x, Value.y, Value.z, Value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& Name, const glm::mat3& Matrix) const
	{
		int32_t pos = glGetUniformLocation(m_RendererId, Name.c_str());
		glUniformMatrix3fv(pos, 1, GL_FALSE, glm::value_ptr(Matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix) const
	{
		int32_t pos = glGetUniformLocation(m_RendererId, Name.c_str());
		glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(Matrix));
	}
}