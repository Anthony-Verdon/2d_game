#include "Engine/LineRenderer/LineRenderer.hpp"
#include "Engine/Shader/Shader.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"

LineRenderer::LineRenderer(): LineData()
{
    Init();
}

LineRenderer::LineRenderer(const glm::vec2 &start, const glm::vec2 &end,const glm::vec3 &color): LineData(start, end, color)
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
    float vertices[] = {start.x, start.y,  end.x, end.y};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LineRenderer::Draw()
{
    float vertices[] = {start.x, start.y,  end.x, end.y};

    Shader *lineShader = RessourceManager::GetShader("Line");
    lineShader->use();
    lineShader->setVec3("color", color);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}