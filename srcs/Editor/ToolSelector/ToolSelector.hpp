#pragma once

#include <unordered_map>
#include <string>
#include <memory>

//@todo do more class like this, at least for getter/setter
class ATool
{
    private:
        std::string name;
    public:
        ATool() {name = "";}
        ATool(const std::string &name) {this->name = name;}
        virtual ~ATool() {}

        virtual void Draw() = 0;

        std::string GetName() const {return (name);}
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