#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer
{
	class ShaderProgram;
}

class ResourceManager
{
public:
	ResourceManager(const std::string& ExecutablePath);

	ResourceManager(ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager& operator =(ResourceManager&&ShaderProgram) noexcept;
	ResourceManager(ResourceManager&&ShaderProgram) noexcept;

	std::shared_ptr<Renderer::ShaderProgram> LoadShader(const std::string&ShaderName, const std::string&VertexPath, const std::string&FragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> GetShader(const std::string&ShaderName);

private:
	std::string GetFileString(const std::string& RelativeFilePath) const;

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> SharedProgramMap;
	SharedProgramMap mShaderPrograms;

	std::string Path;

};
