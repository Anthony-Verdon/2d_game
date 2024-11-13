#pragma once

#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <glm/glm.hpp>
#include <vector>

class Animator
{
    private:
        std::vector<Sprite> frames;
        float animationSpeed;
        float timer;
        unsigned int frameIndex;

    public:
        Animator();
        Animator(float animationSpeed);
        ~Animator();

        void AddFrame(const Sprite &frame);
        void SetAnimationSpeed(float animationSpeed);
        void Update();

        Sprite GetFrame() const;
};