#include "Game.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Time/Time.hpp"
#include "globals.hpp"
#include <glm/gtc/matrix_transform.hpp>

Game::Game()
{
    RessourceManager::AddShader("Sprite", "shaders/sprite/sprite.vs", "shaders/sprite/sprite.fs");
    RessourceManager::AddShader("Line", "shaders/line/line.vs", "shaders/line/line.fs");
    RessourceManager::AddTexture("TileMapDungeon", "assets/tilemap_packed.png");
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
    RessourceManager::GetShader("Sprite")->use();
    RessourceManager::GetShader("Sprite")->setInt("image", 0);
    RessourceManager::GetShader("Sprite")->setMat4("projection", projection);
    RessourceManager::GetShader("Line")->use();
    RessourceManager::GetShader("Line")->setMat4("projection", projection);

   
}

Game::~Game()
{

}

void Game::Run()
{
    Time::updateTime();
    ProcessInput();
    if (player.GetHitbox().IsColliding(barrel.GetHitbox()))
        std::cout << "colliding" << std::endl;
    player.Draw();
    barrel.Draw();
    
}

void Game::ProcessInput()
{
    if (WindowManager::IsKeyPressed(GLFW_KEY_ESCAPE))
        WindowManager::StopUpdateLoop();

    glm::vec2 direction;
    direction.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    direction.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    player.Move(direction);
}