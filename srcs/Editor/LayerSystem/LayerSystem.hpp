#pragma once

class LayerSystem
{
    private:
        int layer;
        bool isHoveredOrFocused;

    public:
        LayerSystem();
        ~LayerSystem();

        void Draw();
        int GetLayer() const;
        bool IsHoveredOrFocused() const;
};