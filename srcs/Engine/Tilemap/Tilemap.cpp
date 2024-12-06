#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
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
        tile.position = glm::vec2(it["position"][0], it["position"][1]);
        tile.size = glm::vec2(it["size"][0], it["size"][1]);
        tile.sprite.textureName = it["sprite"]["texture"]["name"];
        tile.sprite.textureSize = glm::vec2(it["sprite"]["texture"]["size"][0], it["sprite"]["texture"]["size"][1]);
        tile.sprite.spriteCoords = glm::vec2(it["sprite"]["position"][0], it["sprite"]["position"][1]);
        tile.layer = it["layer"];
        AddTile(tile);
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
        file["tiles"][i]["position"] = {it->position.x, it->position.y};
        file["tiles"][i]["size"] = {it->size.x, it->size.y};
        file["tiles"][i]["sprite"]["texture"]["name"] = it->sprite.textureName;
        file["tiles"][i]["sprite"]["texture"]["size"] = {it->sprite.textureSize.x, it->sprite.textureSize.y};
        file["tiles"][i]["sprite"]["position"] = {it->sprite.spriteCoords.x, it->sprite.spriteCoords.y};
        file["tiles"][i]["layer"] = it->layer;

        i++;

        textures.insert(it->sprite.textureName);
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

void Tilemap::AddTile(const Tile &tile)
{
    SuppressTile(tile.position, tile.layer);
    tiles.insert(tile);
}

void Tilemap::AddTile(const glm::vec2 &position, const glm::vec2 &size, const Sprite &sprite, int layer)
{
    Tile tile;
    tile.position = position;
    tile.size = size;
    tile.sprite = sprite;
    tile.layer = layer;
    AddTile(tile);
}

void Tilemap::SuppressTile(const glm::vec2 &position, int layer)
{
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        if (it->position == position && it->layer == layer)
        {
            tiles.erase(it);
            return;
        }
    }
}

void Tilemap::Draw(bool displayLayer, int layer)
{
    if (!displayLayer)
    {
        for (auto it = tiles.begin(); it != tiles.end(); it++)
            SpriteRenderer::Draw(it->position, it->size, 0, glm::vec3(1, 1, 1), it->sprite, false, false, 1);
    }
    else
    {
        int lastLayerChecked = layer;
        float opacity = 1;
        for (auto it = tiles.begin(); it != tiles.end(); it++)
        {   
            if (it->layer != lastLayerChecked)
            {
                lastLayerChecked = it->layer;
                if (it->layer == layer)
                    opacity = 1;
                else if (it->layer < layer)
                    opacity = 0.5;
                else
                    opacity = 0.2;
            }

            SpriteRenderer::Draw(it->position, it->size, 0, glm::vec3(1, 1, 1), it->sprite, false, false, opacity);
        }
    }
}

const std::set<Tile>& Tilemap::GetTiles() const
{
    return (tiles);
}
