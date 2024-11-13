#pragma once

#include <glm/glm.hpp>
#include <vector>

class Animator
{
    private:
        std::vector<glm::vec2> frames;
        float animationSpeed;
        float timer;
        unsigned int frameIndex;

    public:
        Animator();
        Animator(float animationSpeed);
        ~Animator();

        void AddFrame(const glm::vec2 &frame);
        void SetAnimationSpeed(float animationSpeed);
        void Update();

        glm::vec2 GetFrame() const;
};