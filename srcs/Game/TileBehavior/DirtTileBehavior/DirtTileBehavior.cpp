#include "Game/TileBehavior/DirtTileBehavior/DirtTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"
#include "Engine/TilemapManager/TilemapManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "globals.hpp"

DirtTileBehavior::DirtTileBehavior(): ATileBehavior()
{
    behaviorType = TileBehaviorType::DIRT;

    RessourceManager::AddTexture("farmland", "assets/Tiles/FarmLand/FarmLand_Tile.png");

    Tile farmlandTileBlueprint;
    farmlandTileBlueprint.sprite.textureName = "farmland";
    farmlandTileBlueprint.sprite.textureSize = glm::vec2(7, 8);
    farmlandTileBlueprint.sprite.size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    farmlandTileBlueprint.spriteOffset = glm::vec2(0, 0);

    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(0, 0);
        farmlandTiles[Neighbors::NONE] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(0, 1);
        farmlandTiles[Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(0, 2);
        farmlandTiles[Neighbors::TOP | Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(0, 3);
        farmlandTiles[Neighbors::TOP] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(1, 0);
        farmlandTiles[Neighbors::RIGHT + Neighbors::BOTTOM + Neighbors::BOTTOM_RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(1, 1);
        farmlandTiles[Neighbors::TOP + Neighbors::TOP_RIGHT + Neighbors::RIGHT + Neighbors::BOTTOM + Neighbors::BOTTOM_RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(1, 2);
        farmlandTiles[Neighbors::TOP + Neighbors::TOP_RIGHT + Neighbors::RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(1, 3);
        farmlandTiles[Neighbors::RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(2, 0);
        farmlandTiles[Neighbors::LEFT + Neighbors::BOTTOM_LEFT + Neighbors::RIGHT + Neighbors::BOTTOM + Neighbors::BOTTOM_RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(2, 1);
        farmlandTiles[Neighbors::LEFT + Neighbors::BOTTOM_LEFT + Neighbors::TOP_LEFT + Neighbors::TOP + Neighbors::TOP_RIGHT + Neighbors::RIGHT + Neighbors::BOTTOM + Neighbors::BOTTOM_RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(2, 2);
        farmlandTiles[Neighbors::LEFT + Neighbors::TOP_LEFT + Neighbors::TOP + Neighbors::TOP_RIGHT + Neighbors::RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(2, 3);
        farmlandTiles[Neighbors::LEFT + Neighbors::RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(3, 0);
        farmlandTiles[Neighbors::LEFT + Neighbors::BOTTOM_LEFT + Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(3, 1);
        farmlandTiles[Neighbors::LEFT + Neighbors::BOTTOM_LEFT + Neighbors::TOP_LEFT + Neighbors::TOP + Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(3, 2);
        farmlandTiles[Neighbors::LEFT + Neighbors::TOP_LEFT + Neighbors::TOP] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(3, 3);
        farmlandTiles[Neighbors::LEFT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(4, 0);
        farmlandTiles[Neighbors::RIGHT + Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(4, 1);
        farmlandTiles[Neighbors::TOP + Neighbors::RIGHT + Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(4, 2);
        farmlandTiles[Neighbors::TOP + Neighbors::RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(5, 0);
        farmlandTiles[Neighbors::LEFT + Neighbors::RIGHT + Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(5, 1);
        farmlandTiles[Neighbors::LEFT + Neighbors::TOP + Neighbors::RIGHT + Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(5, 2);
        farmlandTiles[Neighbors::LEFT | Neighbors::TOP | Neighbors::RIGHT] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(6, 0);
        farmlandTiles[Neighbors::LEFT | Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(6, 1);
        farmlandTiles[Neighbors::LEFT | Neighbors::TOP | Neighbors::BOTTOM] = farmlandTile;
    }
    {
        Tile farmlandTile = farmlandTileBlueprint;
        farmlandTile.sprite.spriteCoords = glm::vec2(6, 2);
        farmlandTiles[Neighbors::LEFT | Neighbors::TOP] = farmlandTile;
    }
}

DirtTileBehavior::~DirtTileBehavior()
{
}

void DirtTileBehavior::behavior(const std::string &tilemapName, const glm::vec2 &actionCoords)
{
    int neighborsBitfield = 0;

    int bit = 0;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;
            
            Tile tileToFind = TilemapManager::GetTile(tilemapName, actionCoords + glm::vec2(x, y) * SPRITE_SIZE);
            for (auto it = farmlandTiles.begin(); it != farmlandTiles.end(); it++)
            {
                if (it->second == tileToFind)
                {
                    neighborsBitfield += 1 << bit; 
                    break;
                }
            }
            bit++;
        }
    }
    if (farmlandTiles.find(neighborsBitfield) != farmlandTiles.end())
        TilemapManager::AddTile(tilemapName, actionCoords, farmlandTiles[neighborsBitfield]);
    else
    {
        neighborsBitfield = neighborsBitfield & (Neighbors::LEFT | Neighbors::TOP | Neighbors::RIGHT | Neighbors::BOTTOM);
        if (farmlandTiles.find(neighborsBitfield) != farmlandTiles.end())
            TilemapManager::AddTile(tilemapName, actionCoords, farmlandTiles[neighborsBitfield]);
    }
}