#include "Engine/Animator/Animator.hpp"
#include "Engine/Time/Time.hpp"
#include <iostream>

Animator::Animator()
{
    animationSpeed = 1;
    timer = 0;
    frameIndex = 0;
}

Animator::Animator(float animationSpeed)
{
    this->animationSpeed = animationSpeed;
    timer = 0;
    frameIndex = 0;
}

Animator::~Animator()
{
    
}

void Animator::AddFrame(const glm::vec2 &frame)
{
    frames.push_back(frame);
}

void Animator::SetAnimationSpeed(float animationSpeed)
{
    this->animationSpeed = animationSpeed;
}

void Animator::Update()
{
    if (frames.size() == 0)
        return;

    timer += Time::getDeltaTime();
    if (timer > animationSpeed)
    {
        timer = 0;
        frameIndex = (frameIndex + 1) % frames.size();
    }
}

glm::vec2 Animator::GetFrame() const
{
    if (frames.size() == 0)
    {
        std::cerr << "Animator: no frame" << std::endl;
        return (glm::vec2(0, 0));
    }

    return (frames[frameIndex]);
}