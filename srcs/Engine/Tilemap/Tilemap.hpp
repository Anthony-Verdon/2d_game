#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Tile
{
    glm::vec2 position;
    glm::vec2 size;

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
        void AddTile(const glm::vec2 &position, const glm::vec2 &size);
        void Draw();
};