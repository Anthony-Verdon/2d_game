#include "Engine/Animation/Animation.hpp"
#include "Engine/Time/Time.hpp"
#include <iostream>

Animation::Animation()
{
    animationSpeed = 1;
    timer = 0;
    frameIndex = 0;
}

Animation::Animation(float animationSpeed)
{
    this->animationSpeed = animationSpeed;
    timer = 0;
    frameIndex = 0;
}

Animation::~Animation()
{
    
}

void Animation::AddFrame(const Sprite &frame)
{
    frames.push_back(frame);
}

void Animation::SetAnimationSpeed(float animationSpeed)
{
    this->animationSpeed = animationSpeed;
}

void Animation::Update()
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

Sprite Animation::GetFrame() const
{
    if (frames.size() == 0)
        std::cerr << "Animation: no frame" << std::endl;

    return (frames[frameIndex]);
}