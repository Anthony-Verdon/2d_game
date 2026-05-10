#pragma once

#include "Engine/AProgram/AProgram.hpp"
#include "Engine/2D/PhysicBody/PhysicBody.hpp"
#include "Engine/2D/TilemapManager/TilemapManager.hpp"
#include "Engine/2D/Camera2D/Camera2D.hpp"
#include <vector>

#include <box2d/box2d.h>
#include "Game/Player/Player.hpp"
#include "Game/Barrel/Barrel.hpp"
#include "Game/Skeletton/Skeletton.hpp"

class Game : public AProgram
{
  private:
    void ProcessInput();
    void Draw();

    void DebugRendering();

    void LoadChains();
    void LoadTilemapManager();
    void SaveTilemapManager();

    Player player;
    Barrel barrel;
    Skeletton skeletton;

    Camera2D camera;

  public:
    Game();
    ~Game();

    void Init();
    void Run();
    void ScrollCallback(double xOffset, double yOffset);
};