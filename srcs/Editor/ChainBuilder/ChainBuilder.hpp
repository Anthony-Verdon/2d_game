#pragma once

#include <vector>
#include <glm/glm.hpp>

class ChainBuilder
{
    private:
        bool isHoveredOrFocused;
        bool isBuildingChain;

        std::vector<std::vector<glm::vec2>> chains;

    public:
        ChainBuilder();
        ~ChainBuilder();

        void Draw();
        
        void Load();
        void Save();

        bool IsHoveredOrFocused() const;
        bool IsBuildingChain() const;

        void AddPointToChain(const glm::vec2 &point);
        void CloseChain();

        std::vector<std::vector<glm::vec2>> GetChains() const;
};