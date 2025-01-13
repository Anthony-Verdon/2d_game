#pragma once

#include <vector>
#include <string>
#include "globals.hpp"
#include "Editor/AEditorWindow/AEditorWindow.hpp"

class TextureLoader: public AEditorWindow
{
    private:
        char name[INPUT_ARRAY_SIZE];
        char path[INPUT_ARRAY_SIZE];
        std::vector<std::string> textures;

    public:
        TextureLoader();
        ~TextureLoader();

        void Draw();
};