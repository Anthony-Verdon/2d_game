#pragma once

#include "Engine/ATileBehavior/ATileBehavior.hpp"

class DirtTileBehavior: public ATileBehavior
{
    public:
        DirtTileBehavior();
        ~DirtTileBehavior();

        void behavior();
};