#pragma once

enum class TileBehaviorType;

class ATileBehavior
{
    protected:
        TileBehaviorType behaviorType;

    public:
        ATileBehavior() {}
        virtual ~ATileBehavior() {}

        virtual void behavior() = 0;

        TileBehaviorType GetType() {return behaviorType; }

};