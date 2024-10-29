#pragma once

#include "Engine/Shader/Shader.hpp"
#include "Engine/Texture/Texture.hpp"

#include <map>
#include <string>
#include <memory>

class RessourceManager
{
    private:
        RessourceManager() = delete;
        ~RessourceManager() = delete;
    
        static std::map<std::string, std::unique_ptr<Texture>> textures;
        static std::map<std::string,  std::unique_ptr<Shader>> shaders;
    
    public:
        static void AddTexture(const std::string &name, const std::string &texturePath);
        static Texture *GetTexture(const std::string &name);

        static void AddShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
        static Shader *GetShader(const std::string &name);
};