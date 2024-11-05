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
    nbShape = 10;
    int radius = 20;
    glm::vec2 size = glm::vec2(40,40);
    for (int i = 0; i < nbShape; i++)
    {
        glm::vec2 position = glm::vec2(glm::clamp(rand() % WINDOW_WIDTH, radius * 2, WINDOW_WIDTH - radius * 2), glm::clamp(rand() % WINDOW_HEIGHT, radius * 2, WINDOW_HEIGHT - radius * 2));
        glm::vec3 color = glm::vec3((float)(rand() % 256) / 255, (float)(rand() % 256) / 255, (float)(rand() % 256) / 255);
        if (i % 2)
            shapes.push_back(std::make_unique<PolygonRenderer>(SQUARE_VERTICES, SQUARE_FACES, position, 0, size, color, 1, 1));
        else
            shapes.push_back(std::make_unique<CircleRenderer>(position, radius, color, 100, 0, 1, 1));
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
    for (int i = 0; i < nbShape; i++)
    {
        shapes[i]->Step();

        glm::vec2 size;
        CircleRenderer* circle = dynamic_cast<CircleRenderer*>(shapes[i].get());
        if (circle)
            size = glm::vec2(circle->GetRadius(), circle->GetRadius());
        else
        {
            PolygonRenderer* polygon = dynamic_cast<PolygonRenderer*>(shapes[i].get());
            if (polygon)
                size = polygon->GetSize();
        }
        glm::vec2 newPos = shapes[i]->GetPosition();
        if (newPos.x + size.x < 0)
            newPos.x = newPos.x + size.x + WINDOW_WIDTH;
        else if (newPos.x > WINDOW_WIDTH)
            newPos.x = newPos.x - WINDOW_WIDTH;
         if (newPos.y + size.y < 0)
            newPos.y = newPos.y + size.y + WINDOW_HEIGHT;
        else if (newPos.y > WINDOW_HEIGHT)
            newPos.y = newPos.y - WINDOW_HEIGHT;
        shapes[i]->SetPosition(newPos);
        
        shapes[i]->Draw();
    }
    /*
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
        shapes[0]->AddForce(glm::normalize(direction) * speed);
    if (WindowManager::IsKeyPressed(GLFW_KEY_O))
        shapes[0]->Rotate(speed * Time::getDeltaTime() * 100.0f);
    if (WindowManager::IsKeyPressed(GLFW_KEY_P))
        shapes[0]->Rotate(-speed * Time::getDeltaTime() * 100.0f);
}

void Game::CheckCollisions()
{
    for (int i = 0; i < nbShape - 1; i++)
    {
        for (int j = i + 1; j < nbShape; j++)
        {
            Collision collision = CollisionChecker::CheckCollision(shapes[i].get(), shapes[j].get());
            if (collision.doCollide)
            {
                shapes[i]->Move(-1.0f * collision.normal * collision.depth / 2.0f);
                shapes[j]->Move(collision.normal * collision.depth / 2.0f);

                glm::vec2 relativeVelocity = shapes[j]->GetVelocity() - shapes[i]->GetVelocity();
                float e = std::min(shapes[i]->GetRestitution(), shapes[j]->GetRestitution());
                float j2 = -(1.0 + e) * glm::dot(relativeVelocity, collision.normal);
                j2 = j2 / (1.0 / shapes[i]->GetMass() + 1.0 / shapes[j]->GetMass());
                shapes[i]->AddVelocity(-j2 / shapes[i]->GetMass() * collision.normal); 
                shapes[j]->AddVelocity(j2 / shapes[j]->GetMass() * collision.normal); 
            }
        }
    }
}