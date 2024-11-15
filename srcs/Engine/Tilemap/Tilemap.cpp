#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{

}

void Tilemap::Load(const b2WorldId &worldId)
{
    if (!std::filesystem::exists("saves/save.json"))
        return;

    std::ifstream input("saves/save.json");
    nlohmann::json file =  nlohmann::json::parse(input);

    auto itTiles = file.find("tiles");
    for (auto it : *itTiles)
    {
        Tile tile;
        tile.position = glm::vec2(it["position"][0], it["position"][1]);
        tile.size = glm::vec2(it["size"][0], it["size"][1]);

        tile.body = PhysicBody::BodyBuilder().SetPosition(tile.position).SetType(it["type"]).Build(worldId);
        b2Filter filter;
        filter.categoryBits = it["filter"]["category"];
        filter.maskBits = it["filter"]["mask"];
        tile.body.AddShape("tile", PhysicBody::ShapeBuilder().SetFilter(filter).Build(), PhysicBody::PolygonBuilder::Build(tile.size));
        AddTile(tile);
    }
}

void Tilemap::Save()
{
    nlohmann::json file;

    file["tiles"] = {};
    int i = 0;
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        file["tiles"][i]["position"] = {it->position.x, it->position.y};
        file["tiles"][i]["size"] = {it->size.x, it->size.y};
        file["tiles"][i]["type"] = b2Body_GetType(it->body.GetBodyId());
        b2Filter filter = b2Shape_GetFilter(it->body.GetShape("tile"));
        file["tiles"][i]["filter"]["category"] = filter.categoryBits;
        file["tiles"][i]["filter"]["mask"] = filter.maskBits;
        i++;
    }

    std::ofstream o("saves/save.json");
    o << std::setw(4) << file << std::endl;
}

void Tilemap::AddTile(const Tile &tile)
{
    tiles.insert(tile);
}

void Tilemap::AddTile(const glm::vec2 &position, const glm::vec2 &size, const PhysicBody& body)
{
    Tile tile;
    tile.position = position;
    tile.size = size;
    tile.body = body;
    AddTile(tile);
}

void Tilemap::SuppressTile(const glm::vec2 &position)
{
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        if (it->position == position)
        {
            tiles.erase(it);
            return;
        }
    }
}

void Tilemap::Draw()
{
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {   
        Sprite sprite;
        sprite.textureName = "grass";
        sprite.textureSize = glm::vec2(1, 1);
        sprite.spriteCoords = glm::vec2(0, 0);
        SpriteRenderer::Draw(it->position, it->size, 0, glm::vec3(1, 1, 1), sprite, false, false);
    }
}