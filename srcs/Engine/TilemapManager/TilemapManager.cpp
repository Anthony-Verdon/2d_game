#include "Engine/TilemapManager/TilemapManager.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <set>
#include "Engine/RessourceManager/RessourceManager.hpp"

TilemapManager::TilemapManager()
{
}

TilemapManager::~TilemapManager()
{
}

void TilemapManager::AddTile(const std::string &tilemapName, const glm::vec2 &position, const Tile &tile)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.AddTile(position, tile);
}

void TilemapManager::AddTile(const std::string &tilemapName, const glm::vec2 &position, const Sprite &sprite)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.AddTile(position, sprite);
}

void TilemapManager::SuppressTile(const std::string &tilemapName, const glm::vec2 &position)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.SuppressTile(position);
}

void TilemapManager::AddTilemap(const std::string &name, const Tilemap &tilemap)
{
    tilemaps[name] = tilemap;
    tilemapOrder.push_back(name);
}

void TilemapManager::Load()
{
    if (!std::filesystem::exists("saves/map.json")) // @todo: should be a parameter
        return;

    std::ifstream input("saves/map.json");
    nlohmann::ordered_json file =  nlohmann::ordered_json::parse(input);

    auto itTextures = file.find("textures"); //@todo error check
    for (auto it : *itTextures)
    {
        RessourceManager::AddTexture(it["name"], it["path"]);
    }

    auto itTilemaps = file.find("tilemaps"); //@todo error check
    for (auto itTilemap = itTilemaps->begin(); itTilemap != itTilemaps->end(); ++itTilemap)
    {
        std::string tilemapName = itTilemap.key();

        tilemaps[tilemapName] = Tilemap();
        tilemapOrder.push_back(tilemapName);

        auto itTiles = itTilemap->find("tiles");
        for (auto it : *itTiles)
        {
            Tile tile;
            tile.sprite.textureName = it["sprite"]["texture"]["name"];
            tile.sprite.textureSize = glm::vec2(it["sprite"]["texture"]["size"][0], it["sprite"]["texture"]["size"][1]);
            tile.sprite.spriteCoords = glm::vec2(it["sprite"]["position"][0], it["sprite"]["position"][1]);
            tilemaps[tilemapName].AddTile(glm::vec2(it["position"][0], it["position"][1]), tile);
        }
    }
}

void TilemapManager::Save()
{
    nlohmann::ordered_json file;

    file["textures"] = {};
    std::set<std::string> textures;

    file["tilemaps"] = {};
    for (size_t i = 0; i < tilemapOrder.size(); i++ )
    {
        file["tilemaps"][tilemapOrder[i]]["tiles"] = {};
        
        std::map<glm::vec2, Tile, Vec2Comparator> tiles = tilemaps[tilemapOrder[i]].GetTiles();
        int j = 0;
        for (auto it = tiles.begin(); it != tiles.end(); it++)
        {
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["position"] = {it->first.x, it->first.y};
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["sprite"]["texture"]["name"] = it->second.sprite.textureName;
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["sprite"]["texture"]["size"] = {it->second.sprite.textureSize.x, it->second.sprite.textureSize.y};
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["sprite"]["position"] = {it->second.sprite.spriteCoords.x, it->second.sprite.spriteCoords.y};

            j++;

            textures.insert(it->second.sprite.textureName);
        }
    }

    int i = 0;
    for (auto it = textures.begin(); it != textures.end(); it++)
    {
        file["textures"][i]["name"] = *it;
        file["textures"][i]["path"] = RessourceManager::GetTexture(*it)->getPath();

        i++;
    }
    std::ofstream o("saves/map.json");
    o << std::setw(4) << file << std::endl;
}

void TilemapManager::Draw()
{
    for (size_t i = 0; i < tilemapOrder.size(); i++)
        tilemaps[tilemapOrder[i]].Draw();
}

void TilemapManager::AddCollisions(b2WorldId worldId)
{
    for (size_t i = 0; i < tilemapOrder.size(); i++)
        tilemaps[tilemapOrder[i]].CreateTilemapCollision(worldId);
}