#pragma once

#include <unordered_map>
#include <string>
#include <memory>

class ATool
{
    public:
        ATool();
        virtual ~ATool();

        virtual void Draw() = 0;
};

class ToolSelector
{
    private:
        bool isHoveredOrFocused;

        std::unordered_map<std::string, std::pair<bool, std::shared_ptr<ATool>>> tools;

    public:
        ToolSelector();
        ~ToolSelector();

        void Draw();

        bool IsHoveredOrFocused() const;

};