#include "globals.hpp"
#include "Json/Json.hpp"
#include <filesystem>
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/2D/TilemapManager/TilemapManager.hpp"
#include "Engine/2D/TileDictionnary/TileDictionnary.hpp"
#include <set>

void LoadTilemapManager()
{
    if (!std::filesystem::exists(MAP_FILE))
        return;

    Json::Node file = Json::ParseFile(MAP_FILE);

    if (file.KeyExist("textures") && file["textures"] != nullptr)
    {
        auto texturesNode = file["textures"];

        for (auto it = texturesNode.begin(); it != texturesNode.end(); it++)
            RessourceManager::AddTexture(it.key(), (it.value())["path"]);
    }

    if (file.KeyExist("tiles") && file["tiles"] != nullptr)
    {
        for (auto it : file["tiles"])
        {
            Tile tile;
            tile.sprite.textureName = std::string(it["sprite"]["texture"]);
            tile.sprite.textureSize = ml::vec2(file["textures"][tile.sprite.textureName.c_str()]["size"][0], file["textures"][tile.sprite.textureName.c_str()]["size"][1]);
            tile.sprite.spriteCoords = ml::vec2(it["sprite"]["position"][0], it["sprite"]["position"][1]);
            tile.sprite.size = ml::vec2(file["textures"][tile.sprite.textureName.c_str()]["sprite size"][0], file["textures"][tile.sprite.textureName.c_str()]["sprite size"][1]);
            tile.spriteOffset = ml::vec2(file["textures"][tile.sprite.textureName.c_str()]["sprite offset"][0], file["textures"][tile.sprite.textureName.c_str()]["sprite offset"][1]);
            tile.boundingBox = ml::vec2(file["textures"][tile.sprite.textureName.c_str()]["bounding box"][0], file["textures"][tile.sprite.textureName.c_str()]["bounding box"][1]);
            if (it.KeyExist("behaviors") && it["behaviors"] != nullptr)
            {
                for (auto itBehavior : it["behaviors"])
                    tile.behaviors.push_back((TileBehaviorType)(int)itBehavior);
            }
            TileDictionnary::AddTile(tile);
        }
    }

    if (file.KeyExist("tilemaps") && file["tilemaps"] != nullptr)
    {
        Json::Node tilemapsNode = file["tilemaps"];
        for (auto itTilemap = tilemapsNode.begin(); itTilemap != tilemapsNode.end(); ++itTilemap)
        {
            std::string tilemapName = itTilemap.key();

            TilemapManager::AddTilemap(tilemapName);

            Json::Node value = itTilemap.value();
            TilemapManager::SetBuildCollision(tilemapName, value["build collision"]);

            if (value.KeyExist("tiles") && value["tiles"] != nullptr)
            {
                for (auto it : value["tiles"])
                    TilemapManager::AddTile(tilemapName, ml::vec2(it["position"][0], it["position"][1]), it["index"]);
            }
        }
    }
}

void SaveTilemapManager()
{
    Json::Node file;
    if (std::filesystem::exists(MAP_FILE))
        file = Json::ParseFile(MAP_FILE);
    else
        file["textures"] = {};

    file["tiles"] = {};
    for (size_t i = 0; i < TileDictionnary::GetDictionnarySize(); i++)
    {
        Tile tile = TileDictionnary::GetTile(i);
        file["tiles"][i]["sprite"]["texture"] = tile.sprite.textureName;
        file["tiles"][i]["sprite"]["position"][0] = tile.sprite.spriteCoords.x;
        file["tiles"][i]["sprite"]["position"][1] = tile.sprite.spriteCoords.y;
        file["tiles"][i]["behaviors"] = {};
        for (size_t j = 0; j < tile.behaviors.size(); j++)
            file["tiles"][i]["behaviors"][j] = (int)tile.behaviors[j];
    }

    file["tilemaps"] = {};
    std::vector<std::string> tilemapOrder = TilemapManager::GetTilemapOrder();
    for (size_t i = 0; i < tilemapOrder.size(); i++)
    {
        file["tilemaps"][tilemapOrder[i].c_str()]["tiles"] = {};
        file["tilemaps"][tilemapOrder[i].c_str()]["build collision"] = TilemapManager::GetBuildCollision(tilemapOrder[i]);

        std::map<ml::vec2, size_t, Vec2Comparator> tiles = TilemapManager::GetTiles(tilemapOrder[i]);
        int j = 0;
        for (auto it = tiles.begin(); it != tiles.end(); it++)
        {
            file["tilemaps"][tilemapOrder[i].c_str()]["tiles"][j]["position"][0] = it->first.x;
            file["tilemaps"][tilemapOrder[i].c_str()]["tiles"][j]["position"][1] = it->first.y;
            file["tilemaps"][tilemapOrder[i].c_str()]["tiles"][j]["index"] = (int)it->second;

            j++;
        }
    }

    Json::WriteFile(MAP_FILE, file);
}