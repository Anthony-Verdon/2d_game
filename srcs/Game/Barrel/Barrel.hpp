#pragma once

#include "Engine/GameObject/GameObject.hpp"

class Barrel: public GameObject
{
    private:
        glm::vec2 coords;

    public:
        Barrel();
        ~Barrel();
        
        void Draw();
};