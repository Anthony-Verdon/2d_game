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

void DrawSolidPolygonFcn(b2Transform transform, const b2Vec2* vertices, int verticesCount, float radius, b2HexColor color, void *ctx) 
{
    (void)ctx;
    (void)radius;
    glm::vec3 newColor = glm::vec3((float)(color & 0xFF0000) / 255, (float)(color & 0x00FF00) / 255, (float)(color & 0x0000FF) / 255);
    float cosAngle = cos(b2Rot_GetAngle(transform.q));
    float sinAngle = sin(b2Rot_GetAngle(transform.q));
    for (int i = 0; i < verticesCount; i++)
    {   
        b2Vec2 b2va = vertices[i];
        b2Vec2 b2vb = vertices[(i + 1) % verticesCount];
        glm::vec2 va = glm::vec2(PhysicBody::WorldToPixel(transform.p.x + b2va.x * cosAngle - b2va.y * sinAngle), PhysicBody::WorldToPixel(transform.p.y + b2va.x * sinAngle + b2va.y * cosAngle));
        glm::vec2 vb = glm::vec2(PhysicBody::WorldToPixel(transform.p.x + b2vb.x * cosAngle - b2vb.y * sinAngle), PhysicBody::WorldToPixel(transform.p.y + b2vb.x * sinAngle + b2vb.y * cosAngle));
        LineRenderer::Draw(va, vb, newColor);
    }
};

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
    worldDef.gravity = (b2Vec2){0.0f, 0.0f};
    worldId = b2CreateWorld(&worldDef);

    timeStep = 1.0f / 60.0f;
    subStepCount = 4;

    player.Init(worldId);
    barrel.Init(worldId);

    InitDebugDraw();
    debugDraw.DrawSolidPolygon = DrawSolidPolygonFcn;
    debugDraw.drawShapes = true;
}

void Game::InitDebugDraw()
{
    debugDraw.context = NULL;
    debugDraw.DrawCapsule = NULL;
    debugDraw.DrawCircle = NULL;
    debugDraw.DrawPoint = NULL;
    debugDraw.DrawPolygon = NULL;
    debugDraw.DrawSegment = NULL;
    debugDraw.DrawSolidCapsule = NULL;
    debugDraw.DrawSolidCircle = NULL;
    debugDraw.DrawSolidPolygon = NULL;
    debugDraw.DrawString = NULL;
    debugDraw.DrawTransform = NULL;

    debugDraw.drawAABBs = false;
    debugDraw.drawContactImpulses = false;
    debugDraw.drawContactNormals = false;
    debugDraw.drawContacts = false;
    debugDraw.drawFrictionImpulses = false;
    debugDraw.drawGraphColors = false;
    debugDraw.drawJointExtras = false;
    debugDraw.drawJoints = false;
    debugDraw.drawMass = false;
    debugDraw.drawShapes = false;
    debugDraw.useDrawingBounds = false;

    float val = 100;
    b2AABB bounds = {{-val, -val}, {val, val}};
    debugDraw.drawingBounds = bounds;
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

    // tmp, the "camera" follow the player
    glm::vec2 focus = player.GetPosition();
    float left = focus.x - WINDOW_WIDTH / 2;
    float right = focus.x + WINDOW_WIDTH / 2;
    float top = focus.y - WINDOW_HEIGHT / 2;
    float bottom = focus.y + WINDOW_HEIGHT / 2;
    glm::mat4 projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    RessourceManager::GetShader("Sprite")->use();
    RessourceManager::GetShader("Sprite")->setMat4("projection", projection);
    RessourceManager::GetShader("Line")->use();
    RessourceManager::GetShader("Line")->setMat4("projection", projection);
    // end tmp

    Draw();
}

void Game::ProcessInput()
{
    if (WindowManager::IsKeyPressed(GLFW_KEY_ESCAPE))
        WindowManager::StopUpdateLoop();

    glm::vec2 direction;
    direction.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    direction.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (direction != glm::vec2(0, 0))
    {
        player.Move(glm::normalize(direction) * 200.0f * Time::getDeltaTime());
    }
    else
    {
        player.Move( glm::vec2(0, 0));
    }

    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        glm::vec2 mousePosition = player.GetPosition() + WindowManager::GetMousePosition() - glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        mousePosition.x = (int)(mousePosition.x / 64.0f) * 64.0f + 32.0f;
        mousePosition.y = (int)(mousePosition.y / 64.0f) * 64.0f + 32.0f;
        tilemap.AddTile(mousePosition);
    }

}

void Game::Draw()
{
    tilemap.Draw();
    player.Draw();
    barrel.Draw();

    for (unsigned int i = 0; i < WINDOW_WIDTH; i += 64)
        LineRenderer::Draw(glm::vec2(i, 0), glm::vec2(i, WINDOW_HEIGHT), glm::vec3(1, 1, 1));
    for (unsigned int i = 0; i < WINDOW_HEIGHT; i += 64)
        LineRenderer::Draw(glm::vec2(0, i), glm::vec2(WINDOW_WIDTH, i), glm::vec3(1, 1, 1));

    b2World_Draw(worldId, &debugDraw);
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