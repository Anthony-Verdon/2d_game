#pragma once

#include <vector>
#include "Matrix/Matrix.hpp"
#include "Editor/ToolSelector/ATool.hpp"

struct Chain
{
    std::vector<ml::vec2> points;
    bool loop;
};

class ChainBuilder : public ATool
{
  private:
    bool isBuildingChain;
    std::vector<Chain> chains;
    ml::vec2 pointSelected;

  public:
    ChainBuilder();
    ~ChainBuilder();

    void Draw();

    void Load();
    void Save();

    bool IsBuildingChain() const;

    void AddPointToChain(const ml::vec2 &point);
    void CloseChain();

    void SelectPoint(size_t chainIndex, size_t pointIndex);
    void UnselectPoint();
    void MoveSelectedPoint(const ml::vec2 &position);

    std::vector<Chain> GetChains() const;
};