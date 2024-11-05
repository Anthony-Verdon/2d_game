#include "Engine/LineRenderer/LineRenderer.hpp"
#include "Engine/Shader/Shader.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"

LineRenderer::LineRenderer():  LineData(), ARenderer()
{
    Init();
}

LineRenderer::LineRenderer(const glm::vec2 &start, const glm::vec2 &end, const glm::vec2 &position, float rotation, const glm::vec3 &color, float mass, float restitution, bool isStatic):  LineData(start, end), ARenderer(color, position, rotation, mass, restitution, isStatic)
{
    Init();
}

LineRenderer::~LineRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void LineRenderer::Init()
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    CalculateMesh();

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LineRenderer::CalculateMesh()
{
    float vertices[] = {start.x, start.y,  end.x, end.y};
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void LineRenderer::Draw()
{
    Shader *lineShader = RessourceManager::GetShader("Line");
    lineShader->use();
    lineShader->setVec3("color", color);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}