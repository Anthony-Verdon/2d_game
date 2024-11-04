#include "Game.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/CollisionChecker/CollisionChecker.hpp"
#include "Engine/Time/Time.hpp"
#include "globals.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <ctime>

Game::Game()
{
    RessourceManager::AddShader("Sprite", "shaders/sprite/sprite.vs", "shaders/sprite/sprite.fs");
    RessourceManager::AddShader("Line", "shaders/line/line.vs", "shaders/line/line.fs");
    RessourceManager::AddShader("Circle", "shaders/circle/circle.vs", "shaders/circle/circle.fs");
    RessourceManager::AddShader("Square", "shaders/square/square.vs", "shaders/square/square.fs");
    RessourceManager::AddTexture("TileMapDungeon", "assets/tilemap_packed.png");
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), 0.0f, -1.0f, 1.0f);
    RessourceManager::GetShader("Sprite")->use();
    RessourceManager::GetShader("Sprite")->setInt("image", 0);
    RessourceManager::GetShader("Sprite")->setMat4("projection", projection);
    RessourceManager::GetShader("Line")->use();
    RessourceManager::GetShader("Line")->setMat4("projection", projection);
    RessourceManager::GetShader("Circle")->use();
    RessourceManager::GetShader("Circle")->setMat4("projection", projection);
    RessourceManager::GetShader("Square")->use();
    RessourceManager::GetShader("Square")->setMat4("projection", projection);
    line.SetStart(glm::vec2(0,0));
    line.SetEnd(glm::vec2(100,100));
    line.SetColor(glm::vec3(1,1,1));
    line.CalculateMesh();

    srand(time(NULL));
    nbCircle = 5;
    int radius = 20;
    for (int i = 0; i < nbCircle; i++)
    {
        glm::vec2 position = glm::vec2(glm::clamp(rand() % WINDOW_WIDTH, radius * 2, WINDOW_WIDTH - radius * 2), glm::clamp(rand() % WINDOW_HEIGHT, radius * 2, WINDOW_HEIGHT - radius * 2));
        glm::vec3 color = glm::vec3((float)(rand() % 256) / 255, (float)(rand() % 256) / 255, (float)(rand() % 256) / 255);
        circles.push_back(std::make_unique<CircleRenderer>(position, radius, color, 100, 0));
    }

    nbSquare = 3;
    glm::vec2 size = {40, 40};
    for (int i = 0; i < nbSquare; i++)
    {
        //glm::vec2 position = glm::vec2(glm::clamp(rand() % WINDOW_WIDTH, (int)size.x, WINDOW_WIDTH - (int)size.x), glm::clamp(rand() % WINDOW_HEIGHT, (int)size.y, WINDOW_HEIGHT - (int)size.y));
        glm::vec2 position = glm::vec2(size.x * 1.5 * (i + 1), size.y);
        glm::vec3 color = glm::vec3((float)(rand() % 256) / 255, (float)(rand() % 256) / 255, (float)(rand() % 256) / 255);
        squares.push_back(std::make_unique<SquareRenderer>(position, 0, size, color));
    }

}

Game::~Game()
{

}

void Game::Run()
{
    Time::updateTime();
    ProcessInput();
    CheckCollisions();
    for (int i = 0; i < nbSquare; i++)
        squares[i]->Draw();

    /*
    for (int i = 0; i < nbCircle; i++)
        circles[i]->Draw();
    barrel.Draw();
    player.Draw();
    line.Draw();
    */
}

void Game::ProcessInput()
{
    if (WindowManager::IsKeyPressed(GLFW_KEY_ESCAPE))
        WindowManager::StopUpdateLoop();

    float speed = 1.5f;
    glm::vec2 direction;
    direction.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    direction.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (direction != glm::vec2(0, 0))
        circles[0]->Move(glm::normalize(direction) * speed * Time::getDeltaTime() * 100.0f);
    direction.x = WindowManager::IsKeyPressed(GLFW_KEY_RIGHT) - WindowManager::IsKeyPressed(GLFW_KEY_LEFT);
    direction.y = WindowManager::IsKeyPressed(GLFW_KEY_DOWN) - WindowManager::IsKeyPressed(GLFW_KEY_UP);
    if (direction != glm::vec2(0, 0))
        squares[0]->Move(glm::normalize(direction) * speed * Time::getDeltaTime() * 100.0f);
    if (WindowManager::IsKeyPressed(GLFW_KEY_O))
        squares[0]->Rotate(speed * Time::getDeltaTime() * 100.0f);
    if (WindowManager::IsKeyPressed(GLFW_KEY_P))
        squares[0]->Rotate(-speed * Time::getDeltaTime() * 100.0f);
}

void Game::CheckCollisions()
{
    /*
    for (int i = 0; i < nbCircle - 1; i++)
    {
        for (int j = i + 1; j < nbCircle; j++)
        {
            Collision collision = CollisionChecker::CircleCollision(circles[i].get(), circles[j].get());
            if (collision.doCollide)
            {
                circles[i]->Move(-1.0f * collision.normal * collision.depth / 2.0f);
                circles[j]->Move(collision.normal * collision.depth / 2.0f);
            }
        }
    }
    */
    for (int i = 0; i < nbSquare - 1; i++)
    {
        for (int j = i + 1; j < nbSquare; j++)
        {
            Collision collision = CollisionChecker::SquareCollision(squares[i].get(), squares[j].get());
            if (collision.doCollide)
            {
                squares[i]->Move(-1.0f * collision.normal * collision.depth / 2.0f);
                squares[j]->Move(collision.normal * collision.depth / 2.0f);
            }
        }
    }
}