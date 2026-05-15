#pragma once

#include <string>
#include <vector>

#include "Engine/2D/Tile/Tile.hpp"
#include "Editor/ToolSelector/ATool.hpp"
#include "imgui.h"

struct TextureData
{
    std::string name;
    std::string path;
    ml::vec2 nbSprite;
    ml::vec2 spriteOffset;
    ml::vec2 boundingBox;
};

class TileSelector : public ATool
{
  private:
    std::vector<TextureData> texturesData;
    Tile tileSelected;

    // multi select
    ImGuiSelectionBasicStorage selection;
    std::vector<bool> selected;
    std::vector<Tile> tilesSelected;

    void InputFields();
    void TilesAdded();
    void CreateDragDropSourceData();

  public:
    TileSelector();
    ~TileSelector();

    void Draw();

    void Load();
    void Save();

    Tile GetTile() const;
};