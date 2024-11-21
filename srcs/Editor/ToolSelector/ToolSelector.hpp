#pragma once

#include <unordered_map>
#include <string>

class ToolSelector
{
    private:
        bool isHoveredOrFocused;

        std::unordered_map<std::string, bool> tools;

    public:
        ToolSelector();
        ~ToolSelector();

        void Draw();

        bool IsHoveredOrFocused() const;

};