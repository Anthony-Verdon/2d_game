#pragma once

#include <glm/glm.hpp>
#include <map>
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <Box2D/Box2D.h>
#include <vector>

struct Tile
{
    Sprite sprite;
    glm::vec2 spriteOffset;
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
        bool buildCollision;

        std::vector<glm::vec2> DetermineChainPath(std::multimap<glm::vec2, glm::vec2, Vec2Comparator> &lines) const;
        void BuildChain(b2WorldId worldId, const std::vector<glm::vec2> &points) const;
    public:
        Tilemap();
        ~Tilemap();

        void AddTile(const glm::vec2 &position, const Tile &tile);
        void AddTile(const glm::vec2 &position, const Sprite &sprite, const glm::vec2 &spriteOffset);
        void SuppressTile(const glm::vec2 &position);

        bool GetBuildCollision() const { return (buildCollision); }
        void SetBuildCollision(bool buildCollision) {this->buildCollision = buildCollision; }
        
        void Draw();

        void CreateTilemapCollision(b2WorldId worldId);

        const std::map<glm::vec2, Tile, Vec2Comparator>& GetTiles() const;
};