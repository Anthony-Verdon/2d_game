#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

unsigned int LineRenderer::VAO = -1;
unsigned int LineRenderer::VBO = -1;
bool LineRenderer::isInit = false;

void LineRenderer::Init()
{
    if (isInit)
    {
        std::cerr << "LineRenderer already initialized" << std::endl;
        return;
    }

    RessourceManager::AddShader("Line", "shaders/line/line.vs", "shaders/line/line.fs");
    std::shared_ptr<Shader> lineShader = RessourceManager::GetShader("Line");
    lineShader->use();
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f);
    lineShader->setMat4("projection", projection);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    float vertices[] = {0, 0,
                        0, 0};

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    isInit = true;
}

void LineRenderer::Destroy()
{
    if (!isInit)
    {
        std::cerr << "LineRenderer not initialized" << std::endl;
        return;
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void LineRenderer::Draw(const glm::vec2 &va, const glm::vec2 &vb, const glm::vec3 &color)
{
    if (!isInit)
    {
        std::cerr << "LineRenderer not initialized" << std::endl;
        return;
    }

    std::shared_ptr<Shader> lineShader = RessourceManager::GetShader("Line");
    lineShader->use();
    lineShader->setVec3("color", color);
    
    float vertices[] = {va.x, va.y, 
                        vb.x, vb.y};
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}