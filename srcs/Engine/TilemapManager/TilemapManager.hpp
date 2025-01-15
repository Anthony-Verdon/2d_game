#pragma once

#include "Engine/Tilemap/Tilemap.hpp"
#include <map>
#include <string>
#include <vector>

class TilemapManager
{
    private:
        std::map<std::string, Tilemap> tilemaps;
        std::vector<std::string> tilemapOrder;

    public:
        TilemapManager();
        ~TilemapManager();

        void AddTilemap(const std::string &name, const Tilemap &tilemap = Tilemap());

        std::vector<std::string> GetTilemapOrder() const { return tilemapOrder; }
        void SetTilemapOrder(const std::vector<std::string> &tilemapOrder) { this->tilemapOrder = tilemapOrder; }
        void Save();
        void Load();

        void Draw();
};