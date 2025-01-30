#pragma once

#include "Engine/Sprite/Sprite.hpp"
#include <glm/glm.hpp>

struct Tile
{
    Sprite sprite;
    glm::vec2 spriteOffset;

    bool operator==(const Tile& other) const
    {
        return (sprite == other.sprite && spriteOffset == other.spriteOffset);
    }

    static Tile none;
};