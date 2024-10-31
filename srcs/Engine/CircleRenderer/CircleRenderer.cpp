#define _USE_MATH_DEFINES
#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <vector>
#include <cmath>

CircleRenderer::CircleRenderer(): GameObject(), CircleData(), ARenderer()
{
    numTriangles = 30;
    Init();
}

CircleRenderer::CircleRenderer(float radius, const glm::vec2 &center, const glm::vec3 &color, unsigned int numTriangles): GameObject(), CircleData(radius, center), ARenderer(color)
{
    this->numTriangles = numTriangles;
    Init();
}

CircleRenderer::~CircleRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void CircleRenderer::Init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    CalculateMesh();

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CircleRenderer::CalculateMesh()
{
    std::vector<float> vertices;
    float prevX = center.x;
    float prevY = center.y - radius;
    float angle = M_PI * 2.0 / numTriangles;
    
    for (unsigned int i = 0; i <= numTriangles; i++)
    {
        float newX = radius * sin(angle * i) + center.x;
        float newY = radius * cos(angle * i) + center.y;
        vertices.push_back(center.x);
        vertices.push_back(center.y);
        vertices.push_back(prevX);
        vertices.push_back(prevY);
        vertices.push_back(newX);
        vertices.push_back(newY);

        prevX = newX;
        prevY = newY;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

void CircleRenderer::Draw()
{
    Shader *circleShader = RessourceManager::GetShader("Circle");
    circleShader->use();
    circleShader->setVec3("color", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (numTriangles + 1) * 3);
    glBindVertexArray(0);
}

void CircleRenderer::SetNumTriangles(unsigned int numTriangles)
{
    this->numTriangles = numTriangles;
}

unsigned int CircleRenderer::GetNumTriangles() const
{
    return (numTriangles);
}