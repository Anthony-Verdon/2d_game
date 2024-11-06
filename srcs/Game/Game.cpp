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
    nbShape = 1;
    shapes.push_back(std::make_unique<PolygonRenderer>(SQUARE_VERTICES, SQUARE_FACES, glm::vec2(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.8), 0, glm::vec2(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.1), glm::vec3(40.0 / 255, 40.0 / 255, 40.0 / 255), 1, 0.5, true));
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
        if (!shapes[i]->IsStatic())
            shapes[i]->Step();  
        
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

    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        glm::vec2 size = glm::vec2(40,40);
        glm::vec3 color = glm::vec3((float)(rand() % 256) / 255, (float)(rand() % 256) / 255, (float)(rand() % 256) / 255);
        shapes.push_back(std::make_unique<PolygonRenderer>(SQUARE_VERTICES, SQUARE_FACES, WindowManager::GetMousePosition(), 0, size, color, 1, 1, false));
        nbShape++;
    }
    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
    {
        int radius = 20;
        glm::vec3 color = glm::vec3((float)(rand() % 256) / 255, (float)(rand() % 256) / 255, (float)(rand() % 256) / 255);
        shapes.push_back(std::make_unique<CircleRenderer>(WindowManager::GetMousePosition(), radius, color, 100, 0, 1, 1, false));
        nbShape++;
    }

    /*
    float speed = 1.0f;
    glm::vec2 direction;
    direction.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    direction.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (direction != glm::vec2(0, 0))
        shapes[0]->AddForce(glm::normalize(direction) * speed);
    if (WindowManager::IsKeyPressed(GLFW_KEY_O))
        shapes[0]->Rotate(speed * Time::getDeltaTime() * 100.0f);
    if (WindowManager::IsKeyPressed(GLFW_KEY_P))
        shapes[0]->Rotate(-speed * Time::getDeltaTime() * 100.0f);
    */
}

void Game::CheckCollisions()
{
    for (int i = 0; i < nbShape - 1; i++)
    {
        for (int j = i + 1; j < nbShape; j++)
        {
            if (shapes[i]->IsStatic() && shapes[j]->IsStatic())
                continue;

            Collision collision = CollisionChecker::CheckCollision(shapes[i].get(), shapes[j].get());
            if (collision.doCollide)
            {
                if (shapes[i]->IsStatic())
                {
                    shapes[j]->Move(collision.normal * collision.depth);
                }
                else if (shapes[j]->IsStatic())
                {
                    shapes[i]->Move(-collision.normal * collision.depth);
                }
                else
                {
                    shapes[i]->Move(-collision.normal * collision.depth / 2.0f);
                    shapes[j]->Move(collision.normal * collision.depth / 2.0f);
                }

                glm::vec2 relativeVelocity = shapes[j]->GetVelocity() - shapes[i]->GetVelocity();
                float e = std::min(shapes[i]->GetRestitution(), shapes[j]->GetRestitution());
                float j2 = -(1.0 + e) * glm::dot(relativeVelocity, collision.normal);
                j2 = j2 / (shapes[i]->GetInversedMass() + shapes[j]->GetInversedMass());
                shapes[i]->AddVelocity(-j2 * shapes[i]->GetInversedMass() * collision.normal); 
                shapes[j]->AddVelocity(j2 * shapes[j]->GetInversedMass() * collision.normal); 
            }
        }
    }
}