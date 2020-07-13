#include "ShaderProgram.h"

#include <iostream>

namespace Renderer
{
	ShaderProgram::ShaderProgram(const std::string &VertexShader, const std::string &FragmentShader)
	{
		GLuint VertexShaderID;
			if (!CreateShader(VertexShader, GL_VERTEX_SHADER, VertexShaderID))
			{
				std::cerr << "VERTEX SHADER compile-time error" << std::endl;
				return;
			}

		GLuint FragmentShaderID;
			if (!CreateShader(FragmentShader, GL_FRAGMENT_SHADER, FragmentShaderID))
			{
				std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
				glDeleteShader(VertexShaderID);
				return;
			}

			ID = glCreateProgram();
			glAttachShader(ID, VertexShaderID);
			glAttachShader(ID, FragmentShaderID);
			glLinkProgram(ID);

			GLint success;
			glGetProgramiv(ID, GL_LINK_STATUS, &success);
			if (!success)
			{
				GLchar infoLog[1024];
				glGetShaderInfoLog(ID, 1024, nullptr, infoLog);
				std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
			}
			else
			{
				bIsCompiled = true;
			}

			glDeleteShader(VertexShaderID);
			glDeleteShader(FragmentShaderID);
	}

	void ShaderProgram::Use() const
	{
		glUseProgram(ID);
	}

	bool ShaderProgram::CreateShader(const std::string & Source, const GLenum ShaderType, GLuint & ShaderID)
	{
		ShaderID = glCreateShader(ShaderType);
		const char* Code = Source.c_str();

		glShaderSource(ShaderID, 1, &Code, nullptr);
		glCompileShader(ShaderID);

		GLint success;
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(ShaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	ShaderProgram & ShaderProgram::operator=(ShaderProgram && ShaderProgram) noexcept
	{
		glDeleteProgram(ID);
		ID = ShaderProgram.ID;
		bIsCompiled = ShaderProgram.bIsCompiled;
		ShaderProgram.ID = 0;
		ShaderProgram.bIsCompiled = false;
		return *this;
	}
	ShaderProgram::ShaderProgram(ShaderProgram && ShaderProgram) noexcept
	{

		ID = ShaderProgram.ID;
		bIsCompiled = ShaderProgram.bIsCompiled;
		ShaderProgram.ID = 0;
		ShaderProgram.bIsCompiled = false;

	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(ID);
	}
}