#pragma once

#include <vector>
#include <string>
#include <map>
#include "Engine\Animation\Animation.hpp"
#include "Editor\TileSelector\TileSelector.hpp"
#include "imgui.h"
#include "globals.hpp"

class AnimatorTMP
{
    private:
        bool isHoveredOrFocused;
        char name[INPUT_ARRAY_SIZE];
        std::vector<TextureData> texturesData;
        std::vector<Sprite> tilesSelected;
        ImGuiSelectionBasicStorage selection;
        std::vector<bool> selected;

        std::map<std::string, Animation> animations;
        std::string animationSelected;

        void DrawSpriteSelector();
        void DrawAnimationsLoader();
        void DrawCurrentAnimation();

    public:
        AnimatorTMP();
        ~AnimatorTMP();
        void Draw();
        
        bool IsHoveredOrFocused() const;
};