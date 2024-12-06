#pragma once

#include <glm/glm.hpp>
#include <set>
#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"

struct Tile
{
    glm::vec2 position;
    glm::vec2 size;
    PhysicBody body;
    Sprite sprite;
    int layer;

    bool operator==(const Tile &other) const {
        return layer == other.layer && position == other.position && size == other.size; 
    }
    bool operator<(const Tile &other) const {
        if (layer != other.layer)
            return layer < other.layer;
        
        return position.x < other.position.x || position.y < other.position.y; 
    }
};

class Tilemap
{
    private:
        std::set<Tile> tiles;

    public:
        Tilemap();
        ~Tilemap();

        void AddTile(const Tile &tile);
        void AddTile(const glm::vec2 &position, const glm::vec2 &size, const PhysicBody& body, const Sprite &sprite, int layer);
        void SuppressTile(const glm::vec2 &position, int layer);
        void Draw(bool displayLayer = false, int layer = 0);
        
        void Load(const b2WorldId &worldId);
        void Save();

        const std::set<Tile>& GetTiles() const;
};