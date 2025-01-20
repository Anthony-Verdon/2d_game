#pragma once

#include "Engine/Tilemap/Tilemap.hpp"
#include <map>
#include <string>
#include <vector>
#include <Box2D/Box2D.h>

class TilemapManager
{
    private:
        std::map<std::string, Tilemap> tilemaps;
        std::vector<std::string> tilemapOrder;

    public:
        TilemapManager();
        ~TilemapManager();

        void AddTile(const std::string &tilemapName, const glm::vec2 &position, const Tile &tile);
        void AddTile(const std::string &tilemapName, const glm::vec2 &position, const Sprite &sprite, const glm::vec2 &spriteOffset);
        void SuppressTile(const std::string &tilemapName, const glm::vec2 &position);
        
        void AddTilemap(const std::string &name, const Tilemap &tilemap = Tilemap());

        std::vector<std::string> GetTilemapOrder() const { return tilemapOrder; }
        void SetTilemapOrder(const std::vector<std::string> &tilemapOrder) { this->tilemapOrder = tilemapOrder; }
        
        void Save();
        void Load();

        void Draw();

        void AddCollisions(b2WorldId worldId);

};