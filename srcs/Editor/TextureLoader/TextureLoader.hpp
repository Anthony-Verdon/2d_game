#pragma once

#include <vector>
#include <string>
#include "globals.hpp"

class TextureLoader
{
    private:
        char name[INPUT_ARRAY_SIZE];
        char path[INPUT_ARRAY_SIZE];
        std::vector<std::string> textures;
        bool isHoveredOrFocused;

    public:
        TextureLoader();
        ~TextureLoader();

        void Draw();

        bool IsHoveredOrFocused() const;
};