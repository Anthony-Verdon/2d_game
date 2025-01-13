#pragma once

#include <vector>
#include <string>
#include <map>
#include "Engine\Animation\Animation.hpp"
#include "Editor\TileSelector\TileSelector.hpp"
#include "Editor\AEditorWindow\AEditorWindow.hpp"
#include "imgui.h"
#include "globals.hpp"

class AnimationCreator: public AEditorWindow
{
    private:
        // input
        char name[INPUT_ARRAY_SIZE];
        std::vector<TextureData> texturesData;

        // multi select
        ImGuiSelectionBasicStorage selection;
        std::vector<bool> selected;
        std::vector<Sprite> tilesSelected;

        // animations created
        std::map<std::string, Animation> animations;

        // current animation
        std::string animationSelected;
        std::vector<int> frameIndex;
        
        void DrawSpriteSelector();
        void CreateDragDropSourceData();
        void DrawAnimationsLoader();
        void DrawCurrentAnimation();

    public:
        AnimationCreator();
        ~AnimationCreator();

        void Draw();

        void Load();
        void Save();
};