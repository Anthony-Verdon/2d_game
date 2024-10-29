#include "Engine/SpriteData/SpriteData.hpp"

SpriteData::SpriteData()
{
    texture = "";
    size = glm::vec2(1, 1);
    rotation = 0;
    color = glm::vec3(1, 1, 1);
}

SpriteData::SpriteData(const std::string &texture, const glm::vec2 &size, float rotation, const glm::vec3 &color)
{
    this->texture = texture;
    this->size = size;
    this->rotation = rotation;
    this->color = color;
}

SpriteData::~SpriteData()
{

}

void SpriteData::SetTexture(const std::string &texture)
{
    this->texture = texture;
}

void SpriteData::SetSize(const glm::vec2 &size)
{
    this->size = size;
}

void SpriteData::SetRotation(float rotation)
{
    this->rotation = rotation;
}

void SpriteData::SetColor(const glm::vec3 &color)
{
    this->color = color;
}