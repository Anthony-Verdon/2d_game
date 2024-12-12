#pragma once

#include <vector>
#include <string>

constexpr int INPUT_ARRAY_SIZE = 100;

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