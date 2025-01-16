#pragma once

#include <glm/glm.hpp>
#include <map>
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <Box2D/Box2D.h>

struct Tile
{
    Sprite sprite;
};

struct Vec2Comparator {
    bool operator()(const glm::vec2& lhs, const glm::vec2& rhs) const {
        if (lhs.x != rhs.x) {
            return lhs.x < rhs.x;
        }
        return lhs.y < rhs.y;
    }
};

class Tilemap
{
    private:
        std::map<glm::vec2, Tile, Vec2Comparator> tiles;

    public:
        Tilemap();
        ~Tilemap();

        void AddTile(const glm::vec2 &position, const Tile &tile);
        void AddTile(const glm::vec2 &position, const Sprite &sprite);
        void SuppressTile(const glm::vec2 &position);
        
        void Draw();

        void CreateClockwiseChain(b2WorldId worldId);

        const std::map<glm::vec2, Tile, Vec2Comparator>& GetTiles() const;
};