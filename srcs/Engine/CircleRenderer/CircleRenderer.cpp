#define _USE_MATH_DEFINES
#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

unsigned int CircleRenderer::VAO = -1;
unsigned int CircleRenderer::nbTriangles = 30;
bool CircleRenderer::isInit = false;

void CircleRenderer::Init()
{
    if (isInit)
    {
        std::cerr << "CircleRenderer already initialized" << std::endl;
        return;
    }

    RessourceManager::AddShader("Circle", "shaders/circle/circle.vs", "shaders/circle/circle.fs");

    // define circle data
    glm::vec2 position = glm::vec2(0, 0);
    unsigned int radius = 1;

    // calculate vertices
    std::vector<float> vertices;
    float prevX = position.x;
    float prevY = position.y - radius;
    float angle = M_PI * 2.0 / nbTriangles;
    
    for (unsigned int i = 0; i <= nbTriangles; i++)
    {
        float newX = radius * sin(angle * i);
        float newY = radius * cos(angle * i);
        vertices.push_back(0);
        vertices.push_back(0);
        vertices.push_back(prevX);
        vertices.push_back(prevY);
        vertices.push_back(newX);
        vertices.push_back(newY);

        prevX = newX;
        prevY = newY;
    }

    // create mesh
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);

    isInit = true;
}

void CircleRenderer::Destroy()
{
    if (!isInit)
    {
        std::cerr << "CircleRenderer not initialized" << std::endl;
        return;
    }
    glDeleteVertexArrays(1, &VAO);
}

void CircleRenderer::Draw(const glm::vec2 &position, float radius, float rotation, const glm::vec3 &color)
{
    if (!isInit)
    {
        std::cerr << "CircleRenderer not initialized" << std::endl;
        return;
    }
    
    Shader *circleShader = RessourceManager::GetShader("Circle");

    circleShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f)); 

    circleShader->setMat4("model", model);
    circleShader->setVec3("color", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (nbTriangles + 1) * 3);
    glBindVertexArray(0);
}