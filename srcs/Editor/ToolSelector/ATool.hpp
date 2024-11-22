#pragma once

#include <string>

//@todo do more class like this, at least for getter/setter
class ATool
{
    private:
        std::string name;

    public:
        ATool() {name = "";}
        ATool(const std::string &name) {this->name = name;}
        virtual ~ATool() {}

        virtual void Load() {}
        virtual void Save() {}

        virtual void Draw() = 0;

        std::string GetName() const {return (name);}
};