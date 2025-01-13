#pragma once

#include "Engine/Tilemap/Tilemap.hpp"
#include "Editor/AEditorWindow/AEditorWindow.hpp"

class LayerSystem: public AEditorWindow
{
    private:
        int layer;
        void Draw() {}

    public:
        LayerSystem();
        ~LayerSystem();

        void Draw(const Tilemap &tilemap);
        int GetLayer() const;
};