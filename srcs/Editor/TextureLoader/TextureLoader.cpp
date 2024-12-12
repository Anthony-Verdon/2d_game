#include "Editor\TextureLoader\TextureLoader.hpp"
#include "imgui.h"

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

void TextureLoader::Draw()
{
    ImGui::Begin("Texture Loader");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::End();
}

bool TextureLoader::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}