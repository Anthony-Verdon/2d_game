#pragma once

#include <vector>
#include <string>

class TextureLoader
{
    private:
        bool isHoveredOrFocused;

    public:
        TextureLoader();
        ~TextureLoader();

        void Draw();

        bool IsHoveredOrFocused() const;
};