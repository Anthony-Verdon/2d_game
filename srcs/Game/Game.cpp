#include "Game.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/2D/TileDictionnary/TileDictionnary.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/2D/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/2D/Renderers/CircleRenderer/CircleRenderer.hpp"
#include "Engine/2D/Renderers/PolygonRenderer/PolygonRenderer.hpp"
#include "Engine/2D/Renderers/LineRenderer2D/LineRenderer2D.hpp"
#include "Engine/2D/PhysicBody/PhysicBody.hpp"
#include "Shapes/pentagon.hpp"
#include "Shapes/square.hpp"
#include "globals.hpp"
#include "Game/CategoriesFilter.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Engine/2D/WorldPhysic/WorldPhysic.hpp"
#include <set>
#include "Game/TileBehavior/TileBehaviorManager.hpp"
#include "Game/LootManager/LootManager.hpp"
#include "Game/Items/ItemDictionnary/ItemDictionnary.hpp"
#include <memory>
#include <filesystem>
#include "Json/Json.hpp"

static void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

Game::Game()
{
    WindowManager::SetScrollCallback(scroll_callback);
    WindowManager::SetUserPointer(this);
    CircleRenderer::Init();
    PolygonRenderer::Init();
    LineRenderer2D::Init();
    SpriteRenderer::Init();

    PolygonRenderer::LoadPolygon("square", SQUARE_VERTICES, SQUARE_FACES);
    PolygonRenderer::LoadPolygon("pentagon", PENTAGON_VERTICES, PENTAGON_FACES);

    RessourceManager::AddTexture("skeletton_mage", "assets/Enemies/Skeleton/Skeleton_Mage.png");
    RessourceManager::AddTexture("chest", "assets/House/Objects/Chest_Anim.png");

    WorldPhysic::Init();

    LoadChains();
    player.Init(WorldPhysic::GetWorldId());
    barrel.Init(WorldPhysic::GetWorldId());
    skeletton.Init(WorldPhysic::GetWorldId());

    LoadTilemapManager();
    TilemapManager::AddCollisions(WorldPhysic::GetWorldId());

    TileBehaviorManager::Init();
    ItemDictionnary::Init();
}

void Game::LoadChains()
{
    if (!std::filesystem::exists(HITBOX_FILE))
        return;

    Json::Node file = Json::ParseFile(HITBOX_FILE);

    if (file.KeyExist("chains") && file["chains"] != nullptr)
    {

        for (auto itChain : file["chains"])
        {
            std::vector<b2Vec2> chain;
            if (itChain.KeyExist("points") && itChain["points"] != nullptr)
            {
                for (auto itPoint : itChain["points"])
                {
                    chain.push_back({PhysicBody::PixelToWorld(itPoint[0]), PhysicBody::PixelToWorld(itPoint[1])});
                }
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
}

void Game::LoadTilemapManager()
{
    if (!std::filesystem::exists(MAP_FILE))
        return;

    Json::Node file = Json::ParseFile(MAP_FILE);

    if (file.KeyExist("textures") && file["textures"] != nullptr)
    {
        for (auto it : file["textures"])
        {
            RessourceManager::AddTexture(it["name"], it["path"]);
        }
    }

    if (file.KeyExist("tiles") && file["tiles"] != nullptr)
    {
        for (auto it : file["tiles"])
        {
            Tile tile;
            tile.sprite.textureName = std::string(it["sprite"]["texture"]["name"]);
            tile.sprite.textureSize = ml::vec2(it["sprite"]["texture"]["size"][0], it["sprite"]["texture"]["size"][1]);
            tile.sprite.spriteCoords = ml::vec2(it["sprite"]["position"][0], it["sprite"]["position"][1]);
            tile.sprite.size = ml::vec2(it["sprite"]["size"][0], it["sprite"]["size"][1]);
            tile.spriteOffset = ml::vec2(it["sprite"]["offset"][0], it["sprite"]["offset"][1]);
            if (it.KeyExist("behaviors") && it["behaviors"] != nullptr)
            {
                for (auto itBehavior : it["behaviors"])
                    tile.behaviors.push_back((TileBehaviorType)(int)itBehavior);
            }
            TileDictionnary::AddTile(tile);
        }
    }

    if (file.KeyExist("tilemaps") && file["tilemaps"] != nullptr)
    {
        Json::Node tilemapsNode = file["tilemaps"];
        for (auto itTilemap = tilemapsNode.begin(); itTilemap != tilemapsNode.end(); ++itTilemap)
        {
            std::string tilemapName = itTilemap.key();

            TilemapManager::AddTilemap(tilemapName);

            Json::Node value = itTilemap.value();
            TilemapManager::SetBuildCollision(tilemapName, value["build collision"]);

            for (auto it : value["tiles"])
            {
                TilemapManager::AddTile(tilemapName, ml::vec2(it["position"][0], it["position"][1]), it["index"]);
            }
        }
    }
}

Game::~Game()
{
    SaveTilemapManager();

    CircleRenderer::Destroy();
    PolygonRenderer::Destroy();
    LineRenderer2D::Destroy();
    SpriteRenderer::Destroy();

    WorldPhysic::Destroy();
}

void Game::SaveTilemapManager()
{
    Json::Node file;

    file["textures"] = {};
    std::set<std::string> textures;

    file["tiles"] = {};
    for (size_t i = 0; i < TileDictionnary::GetDictionnarySize(); i++)
    {
        Tile tile = TileDictionnary::GetTile(i);
        file["tiles"][i]["sprite"]["texture"]["name"] = tile.sprite.textureName;
        file["tiles"][i]["sprite"]["texture"]["size"][0] = tile.sprite.textureSize.x;
        file["tiles"][i]["sprite"]["texture"]["size"][1] = tile.sprite.textureSize.y;
        file["tiles"][i]["sprite"]["position"][0] = tile.sprite.spriteCoords.x;
        file["tiles"][i]["sprite"]["position"][1] = tile.sprite.spriteCoords.y;
        file["tiles"][i]["sprite"]["size"][0] = tile.sprite.size.x;
        file["tiles"][i]["sprite"]["size"][1] = tile.sprite.size.y;
        file["tiles"][i]["sprite"]["offset"][0] = tile.spriteOffset.x;
        file["tiles"][i]["sprite"]["offset"][1] = tile.spriteOffset.y;
        file["tiles"][i]["behaviors"] = {};
        for (size_t j = 0; j < tile.behaviors.size(); j++)
            file["tiles"][i]["behaviors"][j] = (int)tile.behaviors[j];

        textures.insert(tile.sprite.textureName);
    }

    file["tilemaps"] = {};
    std::vector<std::string> tilemapOrder = TilemapManager::GetTilemapOrder();
    for (size_t i = 0; i < tilemapOrder.size(); i++)
    {
        file["tilemaps"][tilemapOrder[i].c_str()]["tiles"] = {};
        file["tilemaps"][tilemapOrder[i].c_str()]["build collision"] = TilemapManager::GetBuildCollision(tilemapOrder[i]);

        std::map<ml::vec2, size_t, Vec2Comparator> tiles = TilemapManager::GetTiles(tilemapOrder[i]);
        int j = 0;
        for (auto it = tiles.begin(); it != tiles.end(); it++)
        {
            file["tilemaps"][tilemapOrder[i].c_str()]["tiles"][j]["position"][0] = it->first.x;
            file["tilemaps"][tilemapOrder[i].c_str()]["tiles"][j]["position"][1] = it->first.y;
            file["tilemaps"][tilemapOrder[i].c_str()]["tiles"][j]["index"] = (int)it->second;

            j++;
        }
    }

    int i = 0;
    for (auto it = textures.begin(); it != textures.end(); it++)
    {
        file["textures"][i]["name"] = *it;
        file["textures"][i]["path"] = RessourceManager::GetTexture(*it)->getPath();

        i++;
    }

    Json::WriteFile(MAP_FILE, file);
}

void Game::Init()
{
}

void Game::Run()
{
    player.Update();
    skeletton.Update();

    b2SensorEvents sensorEvents = b2World_GetSensorEvents(WorldPhysic::GetWorldId());
    for (int i = 0; i < sensorEvents.beginCount; ++i)
    {
        b2SensorBeginTouchEvent *beginTouch = sensorEvents.beginEvents + i;
        void *myUserData = b2Shape_GetUserData(beginTouch->visitorShapeId);
        Skeletton *skeletton = reinterpret_cast<Skeletton *>(myUserData); // not safe
        if (skeletton)
            skeletton->PlayAnimation("hurtDown");
    }

    ProcessInput();
    WorldPhysic::Update();
    LootManager::Update(player.GetPosition());

    camera.SetPosition(player.GetPosition());
    camera.UpdateShaders();

    Draw();
}

void Game::ProcessInput()
{
    if (WindowManager::IsInputPressed(GLFW_KEY_ESCAPE))
        WindowManager::StopUpdateLoop();
}

void Game::Draw()
{
    TilemapManager::Draw();
    player.Draw();
    skeletton.Draw();
    barrel.Draw();
    LootManager::Draw();

    WorldPhysic::DebugDraw();
}

void Game::DebugRendering()
{
    LineRenderer2D::Draw(ml::vec2(64, 0), ml::vec2(128, 0), ml::vec3(0.8, 0.2, 0.3));
    LineRenderer2D::Draw(ml::vec2(128, 0), ml::vec2(128, 64), ml::vec3(0.8, 0.2, 0.3));
    LineRenderer2D::Draw(ml::vec2(128, 64), ml::vec2(64, 64), ml::vec3(0.8, 0.2, 0.3));
    LineRenderer2D::Draw(ml::vec2(64, 64), ml::vec2(64, 0), ml::vec3(0.8, 0.2, 0.3));

    PolygonRenderer::Draw("square", ml::vec2(138, 10), ml::vec2(20, 20), 0, ml::vec3(0.8, 0.2, 0.3));
    PolygonRenderer::Draw("square", ml::vec2(156, 48), ml::vec2(40, 40), 45, ml::vec3(0.2, 0.8, 0.3));
    PolygonRenderer::Draw("pentagon", ml::vec2(158, 106), ml::vec2(60, 60), 0, ml::vec3(0.6, 0.4, 0.8));
    PolygonRenderer::Draw("pentagon", ml::vec2(168, 176), ml::vec2(80, 80), 180, ml::vec3(0.7, 0, 0.8));

    CircleRenderer::Draw(ml::vec2(218, 20), 20, 0, ml::vec3(0.8, 0.2, 0.3));
    CircleRenderer::Draw(ml::vec2(228, 80), 40, 0, ml::vec3(0.2, 0.8, 0.3));
}

void Game::ScrollCallback(double xOffset, double yOffset)
{
    (void)xOffset;
    camera.Zoom(yOffset);
}

static void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    // @PROBLEM
    (void)window;
    (void)xOffset;
    (void)yOffset;
    // Game *game = reinterpret_cast<Game *>(glfwGetWindowUserPointer(window));
    // game->ScrollCallback(xOffset, yOffset);
}