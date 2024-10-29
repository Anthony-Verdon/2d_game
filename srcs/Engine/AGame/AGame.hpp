#pragma once

class AGame
{
    public:
    AGame();
    virtual ~AGame();

    virtual void Run() = 0;
};