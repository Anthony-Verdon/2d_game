#pragma once

enum class TileBehavior;

class ATileBehavior
{
    protected:
        TileBehavior behaviorType;

    public:
        ATileBehavior() {}
        virtual ~ATileBehavior() {}

        virtual void behavior() = 0;

        TileBehavior GetType() {return behaviorType; }

};