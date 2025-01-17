#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include "Engine/PhysicBody/PhysicBody.hpp"
#include "globals.hpp"
#include "Game/CategoriesFilter.hpp"
#include <array>
#include <map>
#include <vector>

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
        SpriteRenderer::Draw(it->first, it->second.sprite.size, 0, glm::vec3(1, 1, 1), it->second.sprite, false, false, 1);

        for (int i = 0; i < 4; i++)
        {
            if (tiles.find(it->first + directions[i]) == tiles.end())
                LineRenderer::Draw(glm::vec2(it->first + points[i].first), glm::vec2(it->first + points[i].second), glm::vec3(1, 0, 0));
        }
    }
}

void Tilemap::CreateTilemapCollision(b2WorldId worldId)
{
    // store each line in a multimap, in both sense (A -> B, A <- B)
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

    // create the path between all the points
    std::vector<std::vector<glm::vec2>> chains;
    while (lines.size() / 2 != 0)
        chains.push_back(DetermineChainPath(lines));

    // build chains
    for (size_t i = 0; i < chains.size(); i++)
        BuildChain(worldId, chains[i]);
}

std::vector<glm::vec2> Tilemap::DetermineChainPath(std::multimap<glm::vec2, glm::vec2, Vec2Comparator> &lines) const
{

    // determine path
    std::vector<glm::vec2> chainPoints;
    glm::vec2 point = lines.begin()->first;
    for (size_t i = 0; i < lines.size() / 2; i++)
    {
        chainPoints.push_back(point);

        bool pointChanged = false;
        for (auto[it, rangeEnd] = lines.equal_range(point); it != rangeEnd; ++it)
        {
            if (std::find(chainPoints.begin(), chainPoints.end(), it->second) == chainPoints.end())
            {
                point = it->second;
                pointChanged = true;
                break;
            }
        }

        if (!pointChanged)
            break;
    }

    // erase path from multimap
    size_t nbPoints = chainPoints.size();
    for (size_t i = 0; i < nbPoints; i++)
    {
        for (auto[it, rangeEnd] = lines.equal_range(chainPoints[i]); it != rangeEnd;)
        {
            if (it->second == chainPoints[(i + 1) % nbPoints] || it->second == chainPoints[(i - 1) % nbPoints])
                it = lines.erase(it);
            else
                it++;
        }
    }

    return (chainPoints);
}

void Tilemap::BuildChain(b2WorldId worldId, const std::vector<glm::vec2> &chain) const
{
    std::vector<b2Vec2> b2Chain;
    for (size_t i = 0; i < chain.size(); i++)
        b2Chain.push_back({PhysicBody::PixelToWorld(chain[i].x), PhysicBody::PixelToWorld(chain[i].y)});

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    b2BodyId myBodyId = b2CreateBody(worldId, &bodyDef);

    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Wall;
    filter.maskBits = CategoriesFilter::Entities;

    b2ChainDef chainDef = b2DefaultChainDef();
    chainDef.points = b2Chain.data();
    chainDef.count = b2Chain.size();
    chainDef.filter = filter;
    chainDef.isLoop = true;
    
    b2CreateChain(myBodyId, &chainDef);
}
const std::map<glm::vec2, Tile, Vec2Comparator>& Tilemap::GetTiles() const
{
    return (tiles);
}
