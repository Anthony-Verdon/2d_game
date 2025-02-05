#include "Editor/Editor.hpp"
#include "Editor/TileSelector/TileSelector.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/Time/Time.hpp"
#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Renderers/PolygonRenderer/PolygonRenderer.hpp"
#include "Engine/Renderers/CircleRenderer/CircleRenderer.hpp"
#include "globals.hpp"
#include "Game/CategoriesFilter.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <string>
#include "Shapes/square.hpp"

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);
void DrawSolidPolygonFcn(b2Transform transform, const b2Vec2* vertices, int verticesCount, float radius, b2HexColor color, void *ctx);

Editor::Editor()
{
    WindowManager::SetScrollCallback(scroll_callback);
    WindowManager::SetUserPointer(this);

    LineRenderer::Init();
    SpriteRenderer::Init();
    PolygonRenderer::Init();
    CircleRenderer::Init();

    PolygonRenderer::LoadPolygon("square", SQUARE_VERTICES, SQUARE_FACES);
    // box2D
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, 0.0f};
    worldId = b2CreateWorld(&worldDef);
    timeStep = 1.0f / 60.0f;
    subStepCount = 4;
    InitDebugDraw();
    debugDraw.DrawSolidPolygon = DrawSolidPolygonFcn;
    debugDraw.drawShapes = true;

    camera.SetPosition(WindowManager::GetWindowSize() / 2.0f);
    camera.UpdateShaders();
    
    tilemapManagerUI.Load();
    tileBehaviorManager.Load();
    animationCreator.Load();
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    fileExplorer.SetDirectoryPath("assets");
}

void Editor::InitDebugDraw()
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

Editor::~Editor()
{
    tilemapManagerUI.Save();
    animationCreator.Save();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    LineRenderer::Destroy();
    SpriteRenderer::Destroy();
    PolygonRenderer::Destroy();
    CircleRenderer::Destroy();
}

void Editor::Run()
{
    Time::updateTime();
    ImGuiWindowHoweredOrFocused = false;

    // windows
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    toolSelector.Draw();
    fileExplorer.Draw();
    tilemapManagerUI.Draw();
    animationCreator.Draw();
    textureLoader.Draw();
    tileBehaviorManager.Draw(); //@todo create a vector holding all

    ImGuiWindowHoweredOrFocused = toolSelector.IsHoveredOrFocused() || fileExplorer.IsHoveredOrFocused() || tilemapManagerUI.IsHoveredOrFocused() || textureLoader.IsHoveredOrFocused() || animationCreator.IsHoveredOrFocused() || tileBehaviorManager.IsHoveredOrFocused();

    ProcessInput();
    Draw();
}

void Editor::ProcessInput()
{
    if (WindowManager::IsKeyPressed(GLFW_KEY_ESCAPE))
        WindowManager::StopUpdateLoop();
    
    UpdateCamera();
    if (dynamic_cast<ChainBuilder*>(toolSelector.GetSelectedTool().get()))
        UpdateChain();
    else if (dynamic_cast<TileSelector*>(toolSelector.GetSelectedTool().get()))
        UpdateTilemap();
}

void Editor::UpdateCamera()
{
    if (ImGuiWindowHoweredOrFocused)
        return;
    
    glm::vec2 direction;
    direction.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    direction.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    
    if (direction != glm::vec2(0, 0))
    {
        camera.Move(glm::normalize(direction) * 200.0f * Time::getDeltaTime());
        camera.UpdateShaders();
    }
}

void Editor::UpdateChain()
{
    if (ImGuiWindowHoweredOrFocused)
        return;
    
    ChainBuilder* chainBuilder = dynamic_cast<ChainBuilder*>(toolSelector.GetSelectedTool().get());
    if (!chainBuilder)
        return;

    glm::vec2 mousePosition = camera.GetPosition() + (WindowManager::GetMousePosition() - WindowManager::GetWindowSize() / 2.0f) * camera.GetZoom() / 100.0f;
    if (chainBuilder->IsBuildingChain())
    {
        static bool mouseButton1Enable = true;
        if (mouseButton1Enable && WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
        {
            chainBuilder->AddPointToChain(mousePosition);
            mouseButton1Enable = false;
        }
        else if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
        {
            chainBuilder->CloseChain();
        }

        if (!WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
            mouseButton1Enable = true;
    }
    else
    {
        if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
        {
            std::vector<Chain> chains = chainBuilder->GetChains();
            for (size_t i = 0; i < chains.size(); i++)
            {
                for (size_t j = 0; j < chains[i].points.size(); j++)
                {
                    if (glm::length(mousePosition - chains[i].points[j]) < CHAIN_POINT_RADIUS)
                    {
                        chainBuilder->SelectPoint(i, j);
                    }
                }
            }
        }
        else if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
        {
             chainBuilder->UnselectPoint();
        }

        chainBuilder->MoveSelectedPoint(mousePosition);
    }
}

void Editor::UpdateTilemap()
{
    if (ImGuiWindowHoweredOrFocused)
        return;

    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        TileSelector * tileSelector = dynamic_cast<TileSelector*>(toolSelector.GetSelectedTool().get());
        if (!tileSelector)
            return;
        Tile actualTile = tileSelector->GetTile();
        if (actualTile.sprite.textureName == "")
            return;
        glm::vec2 mousePosition = camera.GetPosition() + (WindowManager::GetMousePosition() - WindowManager::GetWindowSize() / 2.0f) * camera.GetZoom() / 100.0f;
        if (mousePosition.x < 0)
            mousePosition.x = (int)(mousePosition.x / SPRITE_SIZE) - 1;
        else
            mousePosition.x = (int)(mousePosition.x / SPRITE_SIZE);
        if (mousePosition.y < 0)
            mousePosition.y = (int)(mousePosition.y / SPRITE_SIZE) - 1;
        else
            mousePosition.y = (int)(mousePosition.y / SPRITE_SIZE);

        mousePosition = mousePosition * SPRITE_SIZE + SPRITE_SIZE / 2;
        tilemapManagerUI.AddTile(mousePosition, actualTile);
    }
    else if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
    {
        glm::vec2 mousePosition = camera.GetPosition() + (WindowManager::GetMousePosition() - WindowManager::GetWindowSize() / 2.0f) * camera.GetZoom() / 100.0f;
        if (mousePosition.x < 0)
            mousePosition.x = (int)(mousePosition.x / SPRITE_SIZE) - 1;
        else
            mousePosition.x = (int)(mousePosition.x / SPRITE_SIZE);
        if (mousePosition.y < 0)
            mousePosition.y = (int)(mousePosition.y / SPRITE_SIZE) - 1;
        else
            mousePosition.y = (int)(mousePosition.y / SPRITE_SIZE);

        mousePosition = mousePosition * SPRITE_SIZE + SPRITE_SIZE / 2;
        tilemapManagerUI.SuppressTile(mousePosition);
    }
}

void Editor::Draw()
{
    // @todo move this region to another part
    glm::vec2 pos = camera.GetPosition();
    float zoom = camera.GetZoom() / 100;
    int spriteSize = SPRITE_SIZE;
    int startX = (int)(pos.x - WindowManager::GetWindowWidth() / 2 * zoom) / spriteSize * spriteSize - spriteSize;
    int endX = (int)(pos.x + WindowManager::GetWindowWidth() / 2 * zoom) / spriteSize * spriteSize + spriteSize;
    int startY = (int)(pos.y - WindowManager::GetWindowHeight() / 2 * zoom) / spriteSize * spriteSize - spriteSize;
    int endY = (int)(pos.y + WindowManager::GetWindowHeight() / 2 * zoom) / spriteSize * spriteSize + spriteSize;
    for (int i = startX; i <= endX; i += spriteSize)
        LineRenderer::Draw(glm::vec2(i, startY), glm::vec2(i, endY), glm::vec3(1, 1, 1));
    for (int i = startY; i <= endY; i += spriteSize)
        LineRenderer::Draw(glm::vec2(startX, i), glm::vec2(endX, i), glm::vec3(1, 1, 1));
    // end region

    // @todo move this region to another part
    ChainBuilder* chainBuilder = toolSelector.GetTool<ChainBuilder>().get();
    if (chainBuilder)
    {
        std::vector<Chain> chains = chainBuilder->GetChains();
        for (size_t i = 0; i < chains.size(); i++)
        {
            Chain chain = chains[i];
            if (chain.points.size() == 0)
                continue;

            for (size_t j = 0; j < chain.points.size() - 1; j++)
            {
                LineRenderer::Draw(chain.points[j], chain.points[j + 1], glm::vec3(0, 0, 0)); //@todo could do define for colors
            }
            if (chainBuilder->IsBuildingChain() && i == chains.size() - 1)
                LineRenderer::Draw(chain.points[chain.points.size() - 1], WindowManager::GetMousePosition(), glm::vec3(0, 0, 0));
            else if (chain.loop)
                LineRenderer::Draw(chain.points[chain.points.size() - 1], chain.points[0], glm::vec3(0, 0, 0));

            for (size_t j = 0; j < chain.points.size(); j++)
            {
                CircleRenderer::Draw(chain.points[j], CHAIN_POINT_RADIUS, 0, glm::vec3(0.7, 0.7, 0.7));
            }
        }
    }
    // end region

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::ScrollCallback(double xOffset, double yOffset)
{
    if (ImGuiWindowHoweredOrFocused)
        return;
    
    (void)xOffset;
    camera.Zoom(yOffset);
    camera.UpdateShaders();
}

static void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    Editor *editor = reinterpret_cast<Editor*>(glfwGetWindowUserPointer(window));
    editor->ScrollCallback(xOffset, yOffset);
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