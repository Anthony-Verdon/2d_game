#include "Engine/SquareRenderer/SquareRenderer.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

SquareRenderer::SquareRenderer(): Transform(), ARenderer()
{
    size = glm::vec2(10, 10);
    Init();
}

SquareRenderer::SquareRenderer(const glm::vec2 &position, float rotation, const glm::vec2 &size, const glm::vec3 &color): Transform(position, rotation), ARenderer(color)
{
    this->size = size;
    Init();
}

SquareRenderer::~SquareRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void SquareRenderer::Init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    CalculateMesh();

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);
}

void SquareRenderer::CalculateMesh()
{
    float vertices[] = { 
        // pos      
        0, 1, 
        1, 0, 
        0, 0, 

        0, 1,
        1, 1, 
        1, 0, 
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}   

void SquareRenderer::Draw()
{
    Shader *squareShader = RessourceManager::GetShader("Square");
    squareShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 

    model = glm::scale(model, glm::vec3(size, 1.0f)); 
    squareShader->setMat4("model", model);
    squareShader->setVec3("color", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SquareRenderer::SetSize(const glm::vec2 &size)
{
    this->size = size;
}

glm::vec2 SquareRenderer::GetSize() const
{
    return (size);
}

float SquareRenderer::GetWidth() const
{
    return (size.x);
}

float SquareRenderer::GetHeight() const
{
    return (size.y);
}