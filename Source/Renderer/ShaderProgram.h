#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string &VertexShader, const std::string &FragmentShader);
		~ShaderProgram();

		bool IsCompiled() const { return bIsCompiled; }
		void Use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator =(ShaderProgram&&ShaderProgram) noexcept;
		ShaderProgram(ShaderProgram&&ShaderProgram) noexcept;
	private:
		bool CreateShader(const std::string &Source, const GLenum ShaderType, GLuint &ShaderID);
		bool bIsCompiled = false;
		GLuint ID = 0;
	};
}