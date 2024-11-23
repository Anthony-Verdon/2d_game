#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Editor/ToolSelector/ATool.hpp"

struct Chain
{
    std::vector<glm::vec2> points;
    bool loop;
};

class ChainBuilder: public ATool
{
    private:
        bool isBuildingChain;
        std::vector<Chain> chains;

    public:
        ChainBuilder();
        ~ChainBuilder();

        void Draw();
        
        void Load();
        void Save();

        bool IsBuildingChain() const;

        void AddPointToChain(const glm::vec2 &point);
        void CloseChain();

        std::vector<Chain> GetChains() const;
};