#define _USE_MATH_DEFINES
#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/LineRenderer/LineRenderer.hpp"
#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

CircleRenderer::CircleRenderer(): ARenderer(RendererType::Circle)
{
    numTriangles = 30;
    radius = 10;
    CalculateInertia();
    Init();
}

CircleRenderer::CircleRenderer(const glm::vec2 &position, float radius, const glm::vec3 &color, unsigned int numTriangles, float rotation, float mass, float restitution, bool isStatic): ARenderer(color, position, rotation, mass, restitution, isStatic, RendererType::Circle)
{
    this->numTriangles = numTriangles;
    this->radius = radius;
    CalculateInertia();
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

    std::vector<float> vertices;
    float prevX = position.x;
    float prevY = position.y - radius;
    float angle = M_PI * 2.0 / numTriangles;
    
    for (unsigned int i = 0; i <= numTriangles; i++)
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

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CircleRenderer::Draw()
{
    Shader *circleShader = RessourceManager::GetShader("Circle");
    circleShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  

    model = glm::translate(model, glm::vec3(radius, radius, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-radius, -radius, 0.0f));

    circleShader->setMat4("model", model);
    circleShader->setVec3("color", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, (numTriangles + 1) * 3);
    glBindVertexArray(0);

    LineRenderer line;
    line.SetColor(glm::vec3(1, 1, 1));
    line.SetStart(position);
    line.SetEnd(position + glm::vec2(radius, 0));
    line.CalculateMesh();
    line.Draw();

}

void CircleRenderer::SetNumTriangles(unsigned int numTriangles)
{
    this->numTriangles = numTriangles;
}

unsigned int CircleRenderer::GetNumTriangles() const
{
    return (numTriangles);
}

void CircleRenderer::SetRadius(float radius)
{
    this->radius = radius;
}

float CircleRenderer::GetRadius() const
{
    return (radius);
}

void CircleRenderer::CalculateInertia()
{
    inertia = 1.0f / 2.0f * mass * radius * radius;
    if (isStatic)
        inversedInertia = 0;
    else
        inversedInertia = 1 / inertia;
}

