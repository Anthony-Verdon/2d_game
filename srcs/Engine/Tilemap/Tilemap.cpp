#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <set>
#include "globals.hpp"

Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{

}

void Tilemap::Load()
{
    if (!std::filesystem::exists("saves/map.json")) // @todo: should be a parameter
        return;

    std::ifstream input("saves/map.json");
    nlohmann::json file =  nlohmann::json::parse(input);

    auto itTextures = file.find("textures"); //@todo error check
    for (auto it : *itTextures)
    {
        RessourceManager::AddTexture(it["name"], it["path"]);
    }
    auto itTiles = file.find("tiles"); //@todo error check
    for (auto it : *itTiles)
    {
        Tile tile;
        tile.sprite.textureName = it["sprite"]["texture"]["name"];
        tile.sprite.textureSize = glm::vec2(it["sprite"]["texture"]["size"][0], it["sprite"]["texture"]["size"][1]);
        tile.sprite.spriteCoords = glm::vec2(it["sprite"]["position"][0], it["sprite"]["position"][1]);
        AddTile(glm::vec2(it["position"][0], it["position"][1]), tile);
    }
}

void Tilemap::Save()
{
    nlohmann::json file;

    file["textures"] = {};
    std::set<std::string> textures;

    file["tiles"] = {};
    int i = 0;
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        file["tiles"][i]["position"] = {it->first.x, it->first.y};
        file["tiles"][i]["sprite"]["texture"]["name"] = it->second.sprite.textureName;
        file["tiles"][i]["sprite"]["texture"]["size"] = {it->second.sprite.textureSize.x, it->second.sprite.textureSize.y};
        file["tiles"][i]["sprite"]["position"] = {it->second.sprite.spriteCoords.x, it->second.sprite.spriteCoords.y};

        i++;

        textures.insert(it->second.sprite.textureName);
    }

    i = 0;
    for (auto it = textures.begin(); it != textures.end(); it++)
    {
        file["textures"][i]["name"] = *it;
        file["textures"][i]["path"] = RessourceManager::GetTexture(*it)->getPath();

        i++;
    }
    std::ofstream o("saves/map.json");
    o << std::setw(4) << file << std::endl;
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
        SpriteRenderer::Draw(it->first, glm::vec2(SPRITE_SIZE, SPRITE_SIZE), 0, glm::vec3(1, 1, 1), it->second.sprite, false, false, 1);
}

const std::map<glm::vec2, Tile, Vec2Comparator>& Tilemap::GetTiles() const
{
    return (tiles);
}
