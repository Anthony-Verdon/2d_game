#pragma once

#include <map>
#include <string>
#include "Engine/Animation/Animation.hpp"

class Animator
{
    private:
        std::map<std::string, Animation> animations;
        std::string currentAnimation;

    public:
        Animator();
        ~Animator();

        void AddAnimation(const std::string &name, const Animation &animation);
        void Play(const std::string &name);
        void Update();
        Sprite GetFrame() const;
        bool CurrentAnimationEnded() const;
        std::string GetCurrentAnimation() const;
};