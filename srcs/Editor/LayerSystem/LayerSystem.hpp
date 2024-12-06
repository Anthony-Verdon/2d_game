#pragma once

#include "Engine/Tilemap/Tilemap.hpp"

class LayerSystem
{
    private:
        int layer;
        bool isHoveredOrFocused;

    public:
        LayerSystem();
        ~LayerSystem();

        void Draw(const Tilemap &tilemap);
        int GetLayer() const;
        bool IsHoveredOrFocused() const;
};