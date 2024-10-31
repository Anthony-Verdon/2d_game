#include "Engine/SpriteData/SpriteData.hpp"

SpriteData::SpriteData()
{
    texture = "";
    size = glm::vec2(1, 1);
    rotation = 0;
}

SpriteData::SpriteData(const std::string &texture, const glm::vec2 &size, float rotation)
{
    this->texture = texture;
    this->size = size;
    this->rotation = rotation;
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