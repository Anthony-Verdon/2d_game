#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Engine/PhysicBody/PhysicBody.hpp"

struct Tile
{
    glm::vec2 position;
    glm::vec2 size;
    PhysicBody body;

    bool operator==(const Tile &other) const {
        return position == other.position && size == other.size; 
    }
};

class Tilemap
{
    private:
        std::vector<Tile> tiles;

    public:
        Tilemap();
        ~Tilemap();

        void AddTile(const Tile &tile);
        void AddTile(const glm::vec2 &position, const glm::vec2 &size, const PhysicBody& body);
        void Draw();
};