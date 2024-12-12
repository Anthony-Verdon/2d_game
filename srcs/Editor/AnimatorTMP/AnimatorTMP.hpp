#pragma once

#include <vector>
#include <string>
#include "imgui.h"

struct textureTMP
{
    std::string textureName;
    ImVec2 uv0;
    ImVec2 uv1;
};

class AnimatorTMP
{
    private:
        bool isHoveredOrFocused;

        std::vector<textureTMP> sprites;
    public:
        AnimatorTMP();
        ~AnimatorTMP();
        void Draw();
        
        bool IsHoveredOrFocused() const;
};