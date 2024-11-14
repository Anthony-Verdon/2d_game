#include "Engine/Animator/Animator.hpp"
#include <iostream>

Animator::Animator()
{
    currentAnimation = "";
}

Animator::~Animator()
{

}

void Animator::AddAnimation(const std::string &name, const Animation &animation)
{
    animations[name] = animation;
}

void Animator::Play(const std::string &name)
{
    if (!animations[currentAnimation].IsStoppable() && !animations[currentAnimation].Ended())
        return;
    
    if (animations.find(name) == animations.end())
    {
        std::cerr << "Animator::Play() : animation " << name << " not found" << std::endl;
        return;
    }

    if (currentAnimation == name)
        return;

    currentAnimation = name;
    animations[currentAnimation].Reset();

}

void Animator::Update()
{
    if (currentAnimation != "")
        animations[currentAnimation].Update();
}

Sprite Animator::GetFrame()
{
    if (currentAnimation == "")
        std::cerr << "Animator::GetFrame() : no animation added" << std::endl;
    return (animations[currentAnimation].GetFrame());
}