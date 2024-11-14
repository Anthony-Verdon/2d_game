#pragma once

#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <glm/glm.hpp>
#include <vector>

class Animation
{
    private:
        std::vector<Sprite> frames;
        float animationSpeed;
        float timer;
        unsigned int frameIndex;
        bool stoppable;
        bool ended;

    public:
        Animation(float animationSpeed = 1.0f, bool stoppable = true);
        ~Animation();

        void AddFrame(const Sprite &frame);
        void Update();
        void Reset();

        void SetAnimationSpeed(float animationSpeed);
        void SetStoppable(bool stoppable);

        bool IsStoppable() const;
        bool Ended() const;
        Sprite GetFrame() const;
        unsigned int GetFrameIndex() const;

        static Animation none;
};