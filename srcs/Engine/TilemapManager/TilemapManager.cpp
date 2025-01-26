#include "Engine/TilemapManager/TilemapManager.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <set>
#include "Engine/RessourceManager/RessourceManager.hpp"

std::map<std::string, Tilemap> TilemapManager::tilemaps;
std::vector<std::string> TilemapManager::tilemapOrder;

void TilemapManager::AddTile(const std::string &tilemapName, const glm::vec2 &position, const Tile &tile)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.AddTile(position, tile);
}

void TilemapManager::AddTile(const std::string &tilemapName, const glm::vec2 &position, const Sprite &sprite, const glm::vec2 &spriteOffset)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.AddTile(position, sprite, spriteOffset);
}

bool TilemapManager::SuppressTile(const std::string &tilemapName, const glm::vec2 &position)
{
    auto it = tilemaps.find(tilemapName);
    if (it == tilemaps.end())
        return (false);

    return (it->second.SuppressTile(position));
}

bool TilemapManager::GetBuildCollision(const std::string &tilemapName)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        return (it->second.GetBuildCollision());

    return (false);
}

void TilemapManager::SetBuildCollision(const std::string &tilemapName, bool buildCollision)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.SetBuildCollision(buildCollision);
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

        tilemaps[tilemapName].SetBuildCollision((*itTilemap)["build collision"]);

        auto itTiles = itTilemap->find("tiles");
        for (auto it : *itTiles)
        {
            Tile tile;
            tile.sprite.textureName = it["sprite"]["texture"]["name"];
            tile.sprite.textureSize = glm::vec2(it["sprite"]["texture"]["size"][0], it["sprite"]["texture"]["size"][1]);
            tile.sprite.spriteCoords = glm::vec2(it["sprite"]["position"][0], it["sprite"]["position"][1]);
            tile.sprite.size = glm::vec2(it["sprite"]["size"][0], it["sprite"]["size"][1]);
            tile.spriteOffset = glm::vec2(it["sprite"]["offset"][0], it["sprite"]["offset"][1]);
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
        file["tilemaps"][tilemapOrder[i]]["build collision"] = tilemaps[tilemapOrder[i]].GetBuildCollision();
        
        std::map<glm::vec2, Tile, Vec2Comparator> tiles = tilemaps[tilemapOrder[i]].GetTiles();
        int j = 0;
        for (auto it = tiles.begin(); it != tiles.end(); it++)
        {
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["position"] = {it->first.x, it->first.y};
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["sprite"]["texture"]["name"] = it->second.sprite.textureName;
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["sprite"]["texture"]["size"] = {it->second.sprite.textureSize.x, it->second.sprite.textureSize.y};
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["sprite"]["position"] = {it->second.sprite.spriteCoords.x, it->second.sprite.spriteCoords.y};
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["sprite"]["size"] = {it->second.sprite.size.x, it->second.sprite.size.y};
            file["tilemaps"][tilemapOrder[i]]["tiles"][j]["sprite"]["offset"] = {it->second.spriteOffset.x, it->second.spriteOffset.y};

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
        tilemaps[tilemapOrder[i]].CreateCollision(worldId);
}

void TilemapManager::UpdateCollision(const std::string &tilemapName, b2WorldId worldId)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.UpdateCollision(worldId);
}