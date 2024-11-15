#pragma once

#include <glm/glm.hpp>
#include <set>
#include "Engine/PhysicBody/PhysicBody.hpp"

struct Tile
{
    glm::vec2 position;
    glm::vec2 size;
    PhysicBody body;

    bool operator==(const Tile &other) const {
        return position == other.position && size == other.size; 
    }
    bool operator<(const Tile &other) const {
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
        void AddTile(const glm::vec2 &position, const glm::vec2 &size, const PhysicBody& body);
        void SuppressTile(const glm::vec2 &position);
        void Draw();
};