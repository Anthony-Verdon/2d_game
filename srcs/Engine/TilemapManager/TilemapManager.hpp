#pragma once

#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/TileDictionnary/TileDictionnary.hpp"
#include <map>
#include <string>
#include <vector>
#include <Box2D/Box2D.h>

class TilemapManager
{
    private:
        static std::map<std::string, Tilemap> tilemaps;
        static std::vector<std::string> tilemapOrder;
        static TileDictionnary tileDictionnary;

        TilemapManager() = delete;
        ~TilemapManager() = delete;
    public:

        static void AddTile(const std::string &tilemapName, const glm::vec2 &position, const Tile &tile);
        static void AddTile(const std::string &tilemapName, const glm::vec2 &position, const Sprite &sprite, const glm::vec2 &spriteOffset);
        static void SuppressTile(const std::string &tilemapName, const glm::vec2 &position);
        
        static bool GetBuildCollision(const std::string &tilemapName);
        static void SetBuildCollision(const std::string &tilemapName, bool buildCollision);

        static void AddTilemap(const std::string &name, const Tilemap &tilemap = Tilemap());

        static std::vector<std::string> GetTilemapOrder() { return tilemapOrder; }
        static void SetTilemapOrder(const std::vector<std::string> &tilemapOrder) { TilemapManager::tilemapOrder = tilemapOrder; }
        
        static void Save();
        static void Load();

        static void Draw();

        static void AddCollisions(b2WorldId worldId);

};