#include "Engine/Animation/Animation.hpp"
#include "Engine/Time/Time.hpp"
#include <iostream>

Animation Animation::none;

Animation::Animation(float animationSpeed, bool stoppable)
{
    this->animationSpeed = animationSpeed;
    this->stoppable = stoppable;
    timer = 0;
    frameIndex = 0;
    ended = false;
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

void Animation::SetStoppable(bool stoppable)
{
    this->stoppable = stoppable;
}

void Animation::Update()
{
    if (frames.size() == 0)
        return;

    timer += Time::getDeltaTime();
    if (timer > animationSpeed)
    {
        timer = 0;
        frameIndex++;
        if (frameIndex == frames.size())
        {
            frameIndex = 0;
            ended = true;
        }
    }
}

void Animation::Reset()
{
    timer = 0;
    frameIndex = 0;
    ended = false;
}

Sprite Animation::GetFrame() const
{
    if (frames.size() == 0)
        std::cerr << "Animation: no frame" << std::endl;

    return (frames[frameIndex]);
}

bool Animation::IsStoppable() const
{
    return (stoppable);
}

bool Animation::Ended() const
{
    return (ended);
}

unsigned int Animation::GetFrameIndex() const
{
    return (frameIndex);
}