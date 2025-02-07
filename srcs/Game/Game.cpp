#include "Game.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/TileDictionnary/TileDictionnary.hpp"
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
#include "Game/WorldPhysic/WorldPhysic.hpp"
#include "Game/TileBehavior/TileBehaviorManager.hpp"
#include "Game/LootManager/LootManager.hpp"
#include <memory>

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

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
    RessourceManager::AddTexture("food_icons", "assets/Icons/No Outline/Food_Icons_NO_Outline.png");

    WorldPhysic::Init();

    LoadChains();
    player.Init(WorldPhysic::GetWorldId());
    barrel.Init(WorldPhysic::GetWorldId());
    skeletton.Init(WorldPhysic::GetWorldId());
    TilemapManager::Load();
    TilemapManager::AddCollisions(WorldPhysic::GetWorldId());

    TileBehaviorManager::Init();
    Loot loot;
    loot.position = glm::vec2(0, 0);
    loot.sprite.textureName = "food_icons";
    loot.sprite.textureSize = glm::vec2(8, 9);
    loot.sprite.spriteCoords = glm::vec2(0, 0);
    loot.sprite.size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    LootManager::AddLoot(loot);
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
        b2BodyId myBodyId = b2CreateBody(WorldPhysic::GetWorldId(), &bodyDef);

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

Game::~Game()
{
    TilemapManager::Save();

    CircleRenderer::Destroy();
    PolygonRenderer::Destroy();
    LineRenderer::Destroy();
    SpriteRenderer::Destroy();
    
    WorldPhysic::Destroy();
}

void Game::Run()
{
    Time::updateTime();
    
    player.Update();
    skeletton.Update();

    b2SensorEvents sensorEvents = b2World_GetSensorEvents(WorldPhysic::GetWorldId());
    for (int i = 0; i < sensorEvents.beginCount; ++i)
    {
        b2SensorBeginTouchEvent* beginTouch = sensorEvents.beginEvents + i;
        void* myUserData = b2Shape_GetUserData(beginTouch->visitorShapeId);
        Skeletton *skeletton = reinterpret_cast<Skeletton*>(myUserData); // not safe
        if (skeletton)
            skeletton->PlayAnimation("hurtDown");
    }

    ProcessInput();
    WorldPhysic::Update();

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
    TilemapManager::Draw();
    player.Draw();
    skeletton.Draw();
    barrel.Draw();

    LootManager::UpdateLoot(player.GetPosition());
    
    WorldPhysic::DebugDraw();
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

static void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    Game *game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
    game->ScrollCallback(xOffset, yOffset);
}