#pragma once

#include "Engine/Sprite/Sprite.hpp"
#include "Engine/ATileBehavior/ATileBehavior.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

struct Tile
{
    Sprite sprite;
    glm::vec2 spriteOffset;
    std::vector<std::shared_ptr<ATileBehavior>> behaviors;

    bool operator==(const Tile& other) const
    {
        return (sprite == other.sprite && spriteOffset == other.spriteOffset);
    }

    static Tile none;
};