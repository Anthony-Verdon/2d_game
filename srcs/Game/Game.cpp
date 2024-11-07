#include "Game.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Renderers/CircleRenderer/CircleRenderer.hpp"
#include "Engine/Renderers/PolygonRenderer/PolygonRenderer.hpp"
#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include "Engine/CollisionChecker/CollisionChecker.hpp"
#include "Engine/Time/Time.hpp"
#include "globals.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <ctime>

Game::Game()
{
    CircleRenderer::Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    PolygonRenderer::Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    LineRenderer::Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    SpriteRenderer::Init(WINDOW_WIDTH, WINDOW_HEIGHT);

    PolygonRenderer::LoadPolygon("square", SQUARE_VERTICES, SQUARE_FACES);
    PolygonRenderer::LoadPolygon("pentagon", PENTAGON_VERTICES, PENTAGON_FACES);

    RessourceManager::AddTexture("TileMapDungeon", "assets/tilemap_packed.png");

    srand(time(NULL));
    shapes.push_back(std::make_unique<PolygonBody>(SQUARE_VERTICES, SQUARE_FACES, glm::vec2(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.8), 0, glm::vec2(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.1), glm::vec3(40.0 / 255, 40.0 / 255, 40.0 / 255), 1, 0.5, true));
    shapes.push_back(std::make_unique<PolygonBody>(SQUARE_VERTICES, SQUARE_FACES, glm::vec2(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.5), 30, glm::vec2(WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.05), glm::vec3(40.0 / 255, 40.0 / 255, 40.0 / 255), 1, 0.5, true));
    shapes.push_back(std::make_unique<PolygonBody>(SQUARE_VERTICES, SQUARE_FACES, glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.2), 330, glm::vec2(WINDOW_WIDTH * 0.35, WINDOW_HEIGHT * 0.05), glm::vec3(40.0 / 255, 40.0 / 255, 40.0 / 255), 1, 0.5, true));
}

Game::~Game()
{
    CircleRenderer::Destroy();
    PolygonRenderer::Destroy();
    LineRenderer::Destroy();
    SpriteRenderer::Destroy();
}

void Game::Run()
{
    Time::updateTime();
    ProcessInput();
    //int iterations = 100;

    /*
    SpriteRenderer::Draw(glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), glm::vec2(64, 64), 0, glm::vec3(1, 1, 1), "TileMapDungeon", glm::vec2(12,11), glm::vec2(10,6));
    */
    /*
    LineRenderer::Draw(glm::vec2(0, 0), glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT), glm::vec3(0.8, 0.2, 0.3));
    LineRenderer::Draw(glm::vec2(0, WINDOW_HEIGHT), glm::vec2(WINDOW_WIDTH, 0), glm::vec3(0.8, 0.2, 0.3));
    */
    PolygonRenderer::Draw("square", glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), glm::vec2(20, 20), 45, glm::vec3(0.8, 0.2, 0.3));
    PolygonRenderer::Draw("square", glm::vec2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4), glm::vec2(40, 40), 90, glm::vec3(0.2, 0.8, 0.3));
    PolygonRenderer::Draw("square", glm::vec2(WINDOW_WIDTH / 4 * 3, WINDOW_HEIGHT / 4), glm::vec2(60, 60), 180, glm::vec3(0.2, 0.3, 0.8));
    PolygonRenderer::Draw("pentagon", glm::vec2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 * 3), glm::vec2(80, 80), 270, glm::vec3(0.6, 0.4, 0.8));
    PolygonRenderer::Draw("pentagon", glm::vec2(WINDOW_WIDTH / 4 * 3, WINDOW_HEIGHT / 4 * 3), glm::vec2(100, 100), 360, glm::vec3(0.7, 0, 0.8));
    /*
    CircleRenderer::Draw(glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 20, 0, glm::vec3(0.8, 0.2, 0.3));
    CircleRenderer::Draw(glm::vec2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4), 40, 0, glm::vec3(0.2, 0.8, 0.3));
    CircleRenderer::Draw(glm::vec2(WINDOW_WIDTH / 4 * 3, WINDOW_HEIGHT / 4), 60, 0, glm::vec3(0.2, 0.3, 0.8));
    CircleRenderer::Draw(glm::vec2(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 * 3), 80, 0, glm::vec3(0.6, 0.4, 0.8));
    CircleRenderer::Draw(glm::vec2(WINDOW_WIDTH / 4 * 3, WINDOW_HEIGHT / 4 * 3), 100, 0, glm::vec3(0.7, 0, 0.8));
    */
    /*
    for (int it = 0; it < iterations; it++)
    {
        CheckCollisions();
        for (unsigned int i = 0; i < shapes.size(); i++)
        {
            shapes[i]->Step(iterations);  
        }
    }
    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->Draw();
        glm::vec2 size = glm::vec2(5, 5);
        std::unique_ptr<PolygonBody> polygon = std::make_unique<PolygonBody>(SQUARE_VERTICES, SQUARE_FACES, shapes[i]->GetPosition() - size / 2.0f, 0, size, glm::vec3(0.8,0.3,0.2), 1, 1, true);
        polygon->Draw();
    }
    for (unsigned int i = 0; i < collisions.size(); i++)
    {
        glm::vec2 size = glm::vec2(5,5);
        if (collisions[i].contactCount == 1)
        {
            std::unique_ptr<PolygonBody> polygon = std::make_unique<PolygonBody>(SQUARE_VERTICES, SQUARE_FACES, collisions[i].contact1 - size / 2.0f, 0, size, glm::vec3(0.8,0.3,0.2), 1, 1, true);
            polygon->Draw();
        }
        else if (collisions[i].contactCount == 2)
        {
            std::unique_ptr<PolygonBody> polygonA = std::make_unique<PolygonBody>(SQUARE_VERTICES, SQUARE_FACES, collisions[i].contact1 - size / 2.0f, 0, size, glm::vec3(0.8,0.3,0.2), 1, 1, true);
            std::unique_ptr<PolygonBody> polygonB = std::make_unique<PolygonBody>(SQUARE_VERTICES, SQUARE_FACES, collisions[i].contact2 - size / 2.0f, 0, size, glm::vec3(0.8,0.3,0.2), 1, 1, true);
            polygonA->Draw();
            polygonB->Draw();
        }
    }
    */
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

    static bool mouseButton1 = WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1);
    static bool mouseButton2 = WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2);
    if (!mouseButton1 && WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        glm::vec2 size = glm::vec2(40, 40);
        glm::vec3 color = glm::vec3((float)(rand() % 256) / 255, (float)(rand() % 256) / 255, (float)(rand() % 256) / 255);
        shapes.push_back(std::make_unique<PolygonBody>(SQUARE_VERTICES, SQUARE_FACES, WindowManager::GetMousePosition(), 0, size, color, 40, 0.5, false));
    }
    if (!mouseButton2 && WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
    {
        int radius = 20;
        glm::vec3 color = glm::vec3((float)(rand() % 256) / 255, (float)(rand() % 256) / 255, (float)(rand() % 256) / 255);
        shapes.push_back(std::make_unique<CircleBody>(WindowManager::GetMousePosition(), radius, color, 100, 0, 40, 0.5, false));
    }
    mouseButton1 = WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1);
    mouseButton2 = WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2);

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
    collisions.clear();

    for (unsigned int i = 0; i < shapes.size() - 1; i++)
    {
        for (unsigned int j = i + 1; j < shapes.size(); j++)
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

                collisions.push_back(collision);
            }
        }
    }

    for (unsigned int i = 0; i < collisions.size(); i++)
    {
        float e = std::min(collisions[i].shapeA->GetRestitution(), collisions[i].shapeB->GetRestitution());

        glm::vec2 contactsPoints[2] = {collisions[i].contact1, collisions[i].contact2};
        glm::vec2 impulseArray[2] = {glm::vec2(0, 0), glm::vec2(0, 0)};
        glm::vec2 impulseFrictionArray[2] = {glm::vec2(0, 0), glm::vec2(0, 0)};
        glm::vec2 raArray[2] = {glm::vec2(0, 0), glm::vec2(0, 0)};
        glm::vec2 rbArray[2] = {glm::vec2(0, 0), glm::vec2(0, 0)};
        float jArray[2] = {0, 0};

        for (unsigned int c = 0; c < collisions[i].contactCount; c++)
        {
            glm::vec2 ra = contactsPoints[c] - collisions[i].shapeA->GetPosition();
            glm::vec2 rb = contactsPoints[c] - collisions[i].shapeB->GetPosition();

            raArray[c] = ra;
            rbArray[c] = rb;

            glm::vec2 raPerp = glm::vec2(-ra.y, ra.x);
            glm::vec2 rbPerp = glm::vec2(-rb.y, rb.x);

            glm::vec2 angularLinearVelocityA = raPerp * collisions[i].shapeA->GetAngularVelocity();
            glm::vec2 angularLinearVelocityB = rbPerp * collisions[i].shapeB->GetAngularVelocity();

            glm::vec2 relativeVelocity = (collisions[i].shapeB->GetVelocity() + angularLinearVelocityB) - (collisions[i].shapeA->GetVelocity() + angularLinearVelocityA);

            float contactVelocityMag = glm::dot(relativeVelocity, collisions[i].normal);
            
            float raPerpDotN = glm::dot(raPerp, collisions[i].normal);
            float rbPerpDotN = glm::dot(rbPerp, collisions[i].normal);

            float denom = collisions[i].shapeA->GetInversedMass() + collisions[i].shapeB->GetInversedMass() + (raPerpDotN * raPerpDotN) * collisions[i].shapeA->GetInversedInertia() + (rbPerpDotN * rbPerpDotN) * collisions[i].shapeB->GetInversedInertia();
            jArray[c] = -(1.0f + e) * contactVelocityMag / denom;
            jArray[c] = jArray[c] / collisions[i].contactCount;

            impulseArray[c] = jArray[c] * collisions[i].normal;
        }

        for (unsigned int c = 0; c < collisions[i].contactCount; c++)
        {
            collisions[i].shapeA->AddVelocity(-impulseArray[c] * collisions[i].shapeA->GetInversedMass());
            collisions[i].shapeA->AddAngularVelocity(-1.0f * glm::cross(glm::vec3(raArray[c], 0), glm::vec3(impulseArray[c], 0)).z * collisions[i].shapeA->GetInversedInertia());
            
            collisions[i].shapeB->AddVelocity(impulseArray[c] * collisions[i].shapeB->GetInversedMass());
            collisions[i].shapeB->AddAngularVelocity(glm::cross(glm::vec3(rbArray[c], 0), glm::vec3(impulseArray[c], 0)).z * collisions[i].shapeB->GetInversedInertia());
        }

        for (unsigned int c = 0; c < collisions[i].contactCount; c++)
        {
            glm::vec2 ra = contactsPoints[c] - collisions[i].shapeA->GetPosition();
            glm::vec2 rb = contactsPoints[c] - collisions[i].shapeB->GetPosition();

            raArray[c] = ra;
            rbArray[c] = rb;

            glm::vec2 raPerp = glm::vec2(-ra.y, ra.x);
            glm::vec2 rbPerp = glm::vec2(-rb.y, rb.x);

            glm::vec2 angularLinearVelocityA = raPerp * collisions[i].shapeA->GetAngularVelocity();
            glm::vec2 angularLinearVelocityB = rbPerp * collisions[i].shapeB->GetAngularVelocity();

            glm::vec2 relativeVelocity = (collisions[i].shapeB->GetVelocity() + angularLinearVelocityB) - (collisions[i].shapeA->GetVelocity() + angularLinearVelocityA);

            glm::vec2 tangent = relativeVelocity - glm::dot(relativeVelocity, collisions[i].normal) * collisions[i].normal;
            if (std::abs(tangent.x) < 0.005f && std::abs(tangent.y) < 0.005f) // to avoid problem of comparaison == or != with float values, here nearly zero
                continue;
            else
                tangent = glm::normalize(tangent);

            float raPerpDotT = glm::dot(raPerp, tangent);
            float rbPerpDotT = glm::dot(rbPerp, tangent);

            float denom = collisions[i].shapeA->GetInversedMass() + collisions[i].shapeB->GetInversedMass() + (raPerpDotT * raPerpDotT) * collisions[i].shapeA->GetInversedInertia() + (rbPerpDotT * rbPerpDotT) * collisions[i].shapeB->GetInversedInertia();
            float jt = -glm::dot(relativeVelocity, tangent) / denom;
            jt = jt / collisions[i].contactCount;
            
            impulseFrictionArray[c] = jt * tangent;
        }

        for (unsigned int c = 0; c < collisions[i].contactCount; c++)
        {
            collisions[i].shapeA->AddVelocity(-impulseFrictionArray[c] * collisions[i].shapeA->GetInversedMass());
            collisions[i].shapeA->AddAngularVelocity(-1.0f * glm::cross(glm::vec3(raArray[c], 0), glm::vec3(impulseFrictionArray[c], 0)).z * collisions[i].shapeA->GetInversedInertia());
            
            collisions[i].shapeB->AddVelocity(impulseFrictionArray[c] * collisions[i].shapeB->GetInversedMass());
            collisions[i].shapeB->AddAngularVelocity(glm::cross(glm::vec3(rbArray[c], 0), glm::vec3(impulseFrictionArray[c], 0)).z * collisions[i].shapeB->GetInversedInertia());
        }
    }
}