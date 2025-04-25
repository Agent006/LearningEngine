#include "LEpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace LE
{
	OpenGLShader::OpenGLShader(const std::string& VertexShader, const std::string& FragmentShader)
	{
		// Create an empty vertex shader handle
		uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = VertexShader.c_str();
		glShaderSource(vertexShaderId, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShaderId);

		int32_t isCompiled = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShaderId);

			LE_CORE_ERROR("{0}", infoLog.data());
			LE_CORE_ASSERT(false, "Vertex shader compilation failure!");

			return;
		}

		// Create an empty fragment shader handle
		uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = FragmentShader.c_str();
		glShaderSource(fragmentShaderId, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShaderId);

		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShaderId);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShaderId);

			LE_CORE_ERROR("{0}", infoLog.data());
			LE_CORE_ASSERT(false, "Fragment shader compilation failure!");

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererId = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererId, vertexShaderId);
		glAttachShader(m_RendererId, fragmentShaderId);

		// Link our program
		glLinkProgram(m_RendererId);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		int32_t isLinked = 0;
		glGetProgramiv(m_RendererId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			int32_t maxLength = 0;
			glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererId, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererId);
			// Don't leak shaders either.
			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);

			LE_CORE_ERROR("{0}", infoLog.data());
			LE_CORE_ASSERT(false, "Shader linking failure!");

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererId, vertexShaderId);
		glDetachShader(m_RendererId, fragmentShaderId);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& Name, const glm::mat4& Matrix) const
	{
		int32_t pos = glGetUniformLocation(m_RendererId, Name.c_str());
		glUniformMatrix4fv(pos, 1, GL_FALSE, glm::value_ptr(Matrix));
	}
}