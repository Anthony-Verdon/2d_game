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
#include "Game/CategoriesFilter.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

void DrawSolidPolygonFcn(b2Transform transform, const b2Vec2* vertices, int verticesCount, float radius, b2HexColor color, void *ctx);
void DrawSegmentFcn(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void *context);
void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);
void DrawPointFcn(b2Vec2 p, float size, b2HexColor color, void *context);

Game::Game()
{
    WindowManager::SetScrollCallback(scroll_callback);
    WindowManager::SetUserPointer(this);
    CircleRenderer::Init();
    PolygonRenderer::Init();
    LineRenderer::Init();
    SpriteRenderer::Init();

    PolygonRenderer::LoadPolygon("square", SQUARE_VERTICES, SQUARE_FACES);
    PolygonRenderer::LoadPolygon("pentagon", PENTAGON_VERTICES, PENTAGON_FACES);

    RessourceManager::AddTexture("skeletton_mage", "assets/Enemies/Skeleton/Skeleton_Mage.png");
    RessourceManager::AddTexture("chest", "assets/House/Objects/Chest_Anim.png");
    

    // create world
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, 0.0f};
    worldId = b2CreateWorld(&worldDef);
    timeStep = 1.0f / 60.0f;
    subStepCount = 4;

    LoadChains();
    player.Init(worldId);
    barrel.Init(worldId);
    skeletton.Init(worldId);
    tilemap.Load();

    InitDebugDraw();
    debugDraw.DrawSolidPolygon = DrawSolidPolygonFcn;
    debugDraw.DrawSegment = DrawSegmentFcn;
    debugDraw.DrawPoint = DrawPointFcn;
    debugDraw.drawShapes = true;
}

void Game::LoadChains()
{
    if (!std::filesystem::exists("saves/hitbox.json")) // @todo: should be a parameter
        return;
    
    std::ifstream input("saves/hitbox.json");
    nlohmann::json file =  nlohmann::json::parse(input);

    auto itChains = file.find("chains"); //@todo error check
    for (auto itChain : *itChains)
    {
        std::vector<b2Vec2> chain;
        auto itPoints = itChain.find("points"); //@todo error check
        for (auto itPoint : *itPoints)
        {
            chain.push_back({PhysicBody::PixelToWorld(itPoint[0]), PhysicBody::PixelToWorld(itPoint[1])});
        }

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_staticBody;
        b2BodyId myBodyId = b2CreateBody(worldId, &bodyDef);

        b2Filter filter;
        filter.categoryBits = CategoriesFilter::Wall;
        filter.maskBits = CategoriesFilter::Entities;
        b2ChainDef chainDef = b2DefaultChainDef();
        chainDef.points = chain.data();
        chainDef.count = chain.size();
        chainDef.filter = filter;
        chainDef.isLoop = itChain["loop"];
        
        b2CreateChain(myBodyId, &chainDef);
    }
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
    tilemap.Save();

    CircleRenderer::Destroy();
    PolygonRenderer::Destroy();
    LineRenderer::Destroy();
    SpriteRenderer::Destroy();
    
    b2DestroyWorld(worldId);
}

void Game::Run()
{
    Time::updateTime();
    
    player.Update();
    skeletton.Update();

    b2SensorEvents sensorEvents = b2World_GetSensorEvents(worldId);
    for (int i = 0; i < sensorEvents.beginCount; ++i)
    {
        b2SensorBeginTouchEvent* beginTouch = sensorEvents.beginEvents + i;
        void* myUserData = b2Shape_GetUserData(beginTouch->visitorShapeId);
        Skeletton *skeletton = reinterpret_cast<Skeletton*>(myUserData); // not safe
        if (skeletton)
            skeletton->PlayAnimation("hurtDown");
    }

    ProcessInput();
    b2World_Step(worldId, timeStep, subStepCount);
    
    camera.SetPosition(player.GetPosition());
    camera.UpdateShaders();

    Draw();
}

void Game::ProcessInput()
{
    if (WindowManager::IsKeyPressed(GLFW_KEY_ESCAPE))
        WindowManager::StopUpdateLoop();
}

void Game::Draw()
{
    tilemap.Draw();
    player.Draw();
    skeletton.Draw();
    barrel.Draw();

    b2World_Draw(worldId, &debugDraw);
}

void Game::DebugRendering()
{
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

void Game::ScrollCallback(double xOffset, double yOffset)
{
    (void)xOffset;
    camera.Zoom(yOffset);
}

static void DrawSolidPolygonFcn(b2Transform transform, const b2Vec2* vertices, int verticesCount, float radius, b2HexColor color, void *ctx) 
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
}

static void DrawPointFcn(b2Vec2 p, float size, b2HexColor color, void *context)
{
    (void)p;
    (void)size;
    (void)color;
    (void)context;
}
static void DrawSegmentFcn(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void *context)
{
    (void)context;
    glm::vec2 va = glm::vec2({PhysicBody::WorldToPixel(p1.x), PhysicBody::WorldToPixel(p1.y)}); // @todo WorldToPixel overload taking a glm::vec2 or a b2Vec2 as parameter
    glm::vec2 vb = glm::vec2({PhysicBody::WorldToPixel(p2.x), PhysicBody::WorldToPixel(p2.y)});
    glm::vec3 newColor = glm::vec3((float)(color & 0xFF0000) / 255, (float)(color & 0x00FF00) / 255, (float)(color & 0x0000FF) / 255);
    LineRenderer::Draw(va, vb, newColor);

}
static void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    Game *game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    game->ScrollCallback(xOffset, yOffset);
}