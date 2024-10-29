#include "Engine/RessourceManager/RessourceManager.hpp"

std::map<std::string, std::unique_ptr<Texture>> RessourceManager::textures;
std::map<std::string,  std::unique_ptr<Shader>> RessourceManager::shaders;

void RessourceManager::AddTexture(const std::string &name, const std::string &texturePath)
{
    textures[name] = std::make_unique<Texture>(texturePath);
}

Texture *RessourceManager::GetTexture(const std::string &name)
{
    return (textures[name].get());
}

void RessourceManager::AddShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath)
{
    shaders[name] = std::make_unique<Shader>(vertexPath, fragmentPath);
}

Shader *RessourceManager::GetShader(const std::string &name)
{
    return (shaders[name].get());
}