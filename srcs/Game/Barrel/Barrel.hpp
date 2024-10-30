#pragma once

#include "Engine/GameObject/GameObject.hpp"
#include "Engine/SquareHitbox/SquareHitbox.hpp"

class Barrel: public GameObject
{
    private:
        glm::vec2 coords;

    public:
        Barrel();
        ~Barrel();
        
        const SquareHitbox &GetHitbox() const;

        void Draw();
};