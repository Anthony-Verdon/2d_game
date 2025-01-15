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

        void AddTilemap(const std::string &name, const Tilemap &tilemap);

        void Save();
        void Load();

        void Draw();
};