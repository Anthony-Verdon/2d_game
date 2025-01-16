#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include "Engine/Renderers/CircleRenderer/CircleRenderer.hpp"
#include "globals.hpp"
#include <array>
#include <map>

const std::array<glm::vec2, 4> directions {
    glm::vec2(0, -SPRITE_SIZE), // top
    glm::vec2(SPRITE_SIZE, 0),  // right
    glm::vec2(0, SPRITE_SIZE),  // bottom
    glm::vec2(-SPRITE_SIZE, 0)  // left
};

const std::array<std::pair<glm::vec2, glm::vec2>, 4> points {
    std::make_pair(glm::vec2(-SPRITE_SIZE, -SPRITE_SIZE) / 2.0f, glm::vec2(SPRITE_SIZE, -SPRITE_SIZE) / 2.0f),  // top
    std::make_pair(glm::vec2(SPRITE_SIZE, -SPRITE_SIZE) / 2.0f, glm::vec2(SPRITE_SIZE, SPRITE_SIZE) / 2.0f),    // right
    std::make_pair(glm::vec2(-SPRITE_SIZE, SPRITE_SIZE) / 2.0f, glm::vec2(SPRITE_SIZE, SPRITE_SIZE) / 2.0f),    // bottom
    std::make_pair(glm::vec2(-SPRITE_SIZE, -SPRITE_SIZE) / 2.0f, glm::vec2(-SPRITE_SIZE, SPRITE_SIZE) / 2.0f)   // left
};
        
Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{

}

void Tilemap::AddTile(const glm::vec2 &position, const Tile &tile)
{
    tiles[position] = tile;
}

void Tilemap::AddTile(const glm::vec2 &position, const Sprite &sprite)
{
    Tile tile;
    tile.sprite = sprite;
    AddTile(position, tile);
}

void Tilemap::SuppressTile(const glm::vec2 &position)
{
    auto it = tiles.find(position);
    if (it != tiles.end())
        tiles.erase(it);
}

void Tilemap::Draw()
{
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        SpriteRenderer::Draw(it->first, glm::vec2(SPRITE_SIZE, SPRITE_SIZE), 0, glm::vec3(1, 1, 1), it->second.sprite, false, false, 1);

        for (int i = 0; i < 4; i++)
        {
            if (tiles.find(it->first + directions[i]) == tiles.end())
                LineRenderer::Draw(glm::vec2(it->first + points[i].first), glm::vec2(it->first + points[i].second), glm::vec3(1, 0, 0));
        }
    }
}

void Tilemap::CreateClockwiseChain()
{
    std::multimap<glm::vec2, glm::vec2, Vec2Comparator> lines;
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (tiles.find(it->first + directions[i]) == tiles.end())
            {
                lines.insert({it->first + points[i].first, it->first + points[i].second});
                lines.insert({it->first + points[i].second, it->first + points[i].first});
            }
        }
    }

    glm::vec2 point = lines.begin()->first;
    std::vector<glm::vec2> pointVisited;
    for (size_t i = 0; i < lines.size() / 2; i++)
    {
        pointVisited.push_back(point);

        bool pointChanged = false;
        for (auto[it, rangeEnd] = lines.equal_range(point); it != rangeEnd; ++it)
        {
            if (std::find(pointVisited.begin(), pointVisited.end(), it->second) == pointVisited.end())
            {
                point = it->second;
                pointChanged = true;
                break;
            }
        }

        if (!pointChanged)
            break;
    }
    
}

const std::map<glm::vec2, Tile, Vec2Comparator>& Tilemap::GetTiles() const
{
    return (tiles);
}
