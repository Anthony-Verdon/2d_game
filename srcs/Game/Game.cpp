#include "Game.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Renderers/CircleRenderer/CircleRenderer.hpp"
#include "Engine/Renderers/PolygonRenderer/PolygonRenderer.hpp"
#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include "Engine/Time/Time.hpp"
#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Shapes/pentagon.hpp"
#include "Shapes/square.hpp"
#include "globals.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

const glm::vec2 littleSquareSize = glm::vec2(10, 10);
const glm::vec2 GroundSize = glm::vec2(500, 100);

Game::Game()
{
    CircleRenderer::Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    PolygonRenderer::Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    LineRenderer::Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    SpriteRenderer::Init(WINDOW_WIDTH, WINDOW_HEIGHT);

    PolygonRenderer::LoadPolygon("square", SQUARE_VERTICES, SQUARE_FACES);
    PolygonRenderer::LoadPolygon("pentagon", PENTAGON_VERTICES, PENTAGON_FACES);

    RessourceManager::AddTexture("TileMapDungeon", "assets/tilemap_packed.png");

    // create world
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, 10.0f};
    worldId = b2CreateWorld(&worldDef);

    // create a ground
    ground = PhysicBody::Builder().SetPosition(glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.8)).SetSize(GroundSize).Build(worldId);

    timeStep = 1.0f / 60.0f;
    subStepCount = 4;
}

Game::~Game()
{
    CircleRenderer::Destroy();
    PolygonRenderer::Destroy();
    LineRenderer::Destroy();
    SpriteRenderer::Destroy();
    
    b2DestroyWorld(worldId);
}

void Game::Run()
{
    Time::updateTime();
    
    ProcessInput();
    b2World_Step(worldId, timeStep, subStepCount);
    Draw();
}

void Game::ProcessInput()
{
    if (WindowManager::IsKeyPressed(GLFW_KEY_ESCAPE))
        WindowManager::StopUpdateLoop();

    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        PhysicBody body = PhysicBody::Builder().SetPosition(WindowManager::GetMousePosition()).SetType(b2_dynamicBody).SetSize(littleSquareSize).SetDensity(1.0f).SetFriction(0.3f).Build(worldId);
        boxes.push_back(body);
    }
}

void Game::Draw()
{
    for (unsigned int i = 0; i < boxes.size(); i++)
    {
        PolygonRenderer::Draw("square", boxes[i].GetPosition(), littleSquareSize, boxes[i].GetAngle(), glm::vec3(0.8, 0.2, 0.3));
    }

    PolygonRenderer::Draw("square", ground.GetPosition(), GroundSize, ground.GetAngle(), glm::vec3(0.8, 0.2, 0.3));
}

void Game::DebugRendering()
{
    SpriteRenderer::Draw(glm::vec2(32, 32), glm::vec2(64, 64), 0, glm::vec3(1, 1, 1), "TileMapDungeon", glm::vec2(12,11), glm::vec2(10,6));
    SpriteRenderer::Draw(glm::vec2(32, 96), glm::vec2(64, 64), 0, glm::vec3(1, 1, 1), "TileMapDungeon", glm::vec2(12,11), glm::vec2(0,7));
    
    LineRenderer::Draw(glm::vec2(64, 0), glm::vec2(128, 0), glm::vec3(0.8, 0.2, 0.3));
    LineRenderer::Draw(glm::vec2(128, 0), glm::vec2(128, 64), glm::vec3(0.8, 0.2, 0.3));
    LineRenderer::Draw(glm::vec2(128, 64), glm::vec2(64, 64), glm::vec3(0.8, 0.2, 0.3));
    LineRenderer::Draw(glm::vec2(64, 64), glm::vec2(64, 0), glm::vec3(0.8, 0.2, 0.3));
    
    PolygonRenderer::Draw("square", glm::vec2(138, 10), glm::vec2(20, 20), 0, glm::vec3(0.8, 0.2, 0.3));
    PolygonRenderer::Draw("square", glm::vec2(156, 48), glm::vec2(40, 40), 45, glm::vec3(0.2, 0.8, 0.3));
    PolygonRenderer::Draw("pentagon", glm::vec2(158, 106), glm::vec2(60, 60), 0, glm::vec3(0.6, 0.4, 0.8));
    PolygonRenderer::Draw("pentagon", glm::vec2(168, 176), glm::vec2(80, 80), 180, glm::vec3(0.7, 0, 0.8));
    
    CircleRenderer::Draw(glm::vec2(218, 20), 20, 0, glm::vec3(0.8, 0.2, 0.3));
    CircleRenderer::Draw(glm::vec2(228, 80), 40, 0, glm::vec3(0.2, 0.8, 0.3));
    
}