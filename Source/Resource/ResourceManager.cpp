#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& ExecutablePath)
{
	size_t Found = ExecutablePath.find_last_of("/\\");
	Path = ExecutablePath.substr(0, Found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShader(const std::string & ShaderName, const std::string & VertexPath, const std::string & FragmentPath)
{
	std::string VertexString = GetFileString(VertexPath);
	if (VertexString.empty())
	{
		std::cout<< "No vertex shader" << std::endl;
		return nullptr;
	}

	std::string FragmentString = GetFileString(FragmentPath);
	if (VertexString.empty())
	{
		std::cout << "No fragment shader" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& NewShader = mShaderPrograms.emplace(ShaderName, std::make_shared<Renderer::ShaderProgram >(VertexString, FragmentString)).first->second;
	if (NewShader->IsCompiled())
	{
		return NewShader;
	}

	std::cout << "Cant load shader program/n"
		<< "Vertex: " << VertexPath << "/n"
		<< "Fragment: " << FragmentPath << std::endl;

	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShader(const std::string & ShaderName)
{
	SharedProgramMap::const_iterator It = mShaderPrograms.find(ShaderName);
	if (It!=mShaderPrograms.end())
	{
		return It->second;
	}

	std::cout << "Cant faind shader rpogram " << ShaderName << std::endl;

	return nullptr;
}

std::string ResourceManager::GetFileString(const std::string & RelativeFilePath) const
{
	std::ifstream F;
	F.open(Path + "/" + RelativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!F.is_open())
	{
		std::cout << "Failed open file " << RelativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream Buffer;
	Buffer << F.rdbuf();

	return Buffer.str();
}
