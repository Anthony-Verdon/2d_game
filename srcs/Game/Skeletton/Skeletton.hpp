#pragma once

#include "Engine/2D/PhysicBody/PhysicBody.hpp"
#include "Engine/2D/AnimationManager/AnimationManager.hpp"

class Skeletton
{
    private:
        glm::vec2 size;
        AnimationManager animator;
        PhysicBody body;
        
        void InitAnimations();

    public:
        Skeletton();
        ~Skeletton();

        void Init(b2WorldId worldId);
        void Update();
        void PlayAnimation(const std::string &name);
        void Draw();
};