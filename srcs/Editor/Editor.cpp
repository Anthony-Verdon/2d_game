#include "Editor/Editor.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/Time/Time.hpp"
#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"
#include "Game/CategoriesFilter.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <string>

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);
void DrawSolidPolygonFcn(b2Transform transform, const b2Vec2* vertices, int verticesCount, float radius, b2HexColor color, void *ctx);

Editor::Editor()
{
    WindowManager::SetScrollCallback(scroll_callback);
    WindowManager::SetUserPointer(this);

    LineRenderer::Init();
    SpriteRenderer::Init();

    RessourceManager::AddTexture("grass_tiles", "assets/Tiles/Grass/Grass_Tiles_1.png");

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
    tilemap.Load(worldId);
    actualSprite.textureName = "";

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(WindowManager::GetWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
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
    tilemap.Save();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Editor::Run()
{
    
    Time::updateTime();
    ImGuiWindowHoweredOrFocused = false;

    CreateTileSelector();
    ProcessInput();
    Draw();
}

void Editor::CreateTileSelector()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Tile Selector");

    if (ImGui::IsWindowHovered() || ImGui::IsWindowFocused())
        ImGuiWindowHoweredOrFocused = true;

    std::string textureName = "grass_tiles";
    glm::vec2 textureSize = glm::vec2(8, 10);
    ImVec2 size = ImVec2(TILE_SIZE * 2.0f, TILE_SIZE * 2.0f);
    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    for (int j = 0; j < textureSize.y; j++)
    {
        for (int i = 0; i < textureSize.x; i++)
        {
            ImVec2 uv0 = ImVec2((float)i / textureSize.x,(float)j / textureSize.y); 
            ImVec2 uv1 = ImVec2((float)(i + 1) / textureSize.x, (float)(j + 1) / textureSize.y);
            std::string button = std::to_string(j) + "_" + std::to_string(i);
            if (ImGui::ImageButton(button.c_str(), (ImTextureID)(intptr_t)RessourceManager::GetTexture(textureName)->getID(), size, uv0, uv1, bg_col, tint_col))
            {
                actualSprite.textureName = textureName; 
                actualSprite.textureSize = textureSize; 
                actualSprite.spriteCoords = glm::vec2(i, j); 
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }
    ImGui::End();
}

void Editor::ProcessInput()
{
    if (WindowManager::IsKeyPressed(GLFW_KEY_ESCAPE))
        WindowManager::StopUpdateLoop();
    
    UpdateCamera();
    UpdateTilemap();
}

void Editor::UpdateCamera()
{
    glm::vec2 direction;
    direction.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    direction.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    
    if (direction != glm::vec2(0, 0))
    {
        camera.Move(glm::normalize(direction) * 200.0f * Time::getDeltaTime());
        camera.UpdateShaders();
    }
}

void Editor::UpdateTilemap()
{
    if (ImGuiWindowHoweredOrFocused)
        return;

    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        if (actualSprite.textureName == "")
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
        glm::vec2 size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);

        PhysicBody body = PhysicBody::BodyBuilder().SetPosition(mousePosition).SetType(b2_staticBody).Build(worldId);
        
        b2Filter filter;
        filter.categoryBits = CategoriesFilter::Wall;
        filter.maskBits = CategoriesFilter::Entities;
        
        body.AddShape("tile", PhysicBody::ShapeBuilder().SetFilter(filter).Build(), PhysicBody::PolygonBuilder::Build(size));

        tilemap.AddTile(mousePosition, size, body, actualSprite);
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
        tilemap.SuppressTile(mousePosition);
    }
}

void Editor::Draw()
{
    tilemap.Draw();

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

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::ScrollCallback(double xOffset, double yOffset)
{
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