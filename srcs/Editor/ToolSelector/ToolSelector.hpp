#pragma once

#include <unordered_map>
#include <string>
#include <memory>

class ATool
{
    private:
        std::string name;
    public:
        ATool();
        ATool(const std::string &name);
        virtual ~ATool();

        virtual void Draw() = 0;

        std::string GetName() const;
};

class ToolSelector
{
    private:
        bool isHoveredOrFocused;

        std::unordered_map<std::shared_ptr<ATool>, bool> tools;

    public:
        ToolSelector();
        ~ToolSelector();

        void Draw();

        bool IsHoveredOrFocused() const;

};