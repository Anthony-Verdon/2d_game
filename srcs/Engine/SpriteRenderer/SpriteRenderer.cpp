#include "Engine/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

SpriteRenderer::SpriteRenderer(): GameObject(), Transform(), ARenderer()
{
    texture = "";
    size = glm::vec2(1, 1);
    Init();
}

SpriteRenderer::SpriteRenderer(const std::string &texture, const glm::vec2 &size, const glm::vec2 &position, float rotation, const glm::vec3 &color): GameObject(), Transform(position, rotation), ARenderer(color)
{
    this->texture = texture;
    this->size = size;
    Init();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void SpriteRenderer::Init()
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    SetSprite(glm::vec2(1,1), glm::vec2(0,0));

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);
}

// texture size correspond to the number of sprite on the x axis and the y axis
void SpriteRenderer::SetSprite(const glm::vec2 &textureSize, const glm::vec2 &spriteCoords)
{
    glm::vec2 TopLeftCoords;
    glm::vec2 BotomRightCoords;
    TopLeftCoords.x = 1.0f / textureSize.x * spriteCoords.x;
    TopLeftCoords.y = 1.0f / textureSize.y * spriteCoords.y;
    BotomRightCoords.x = 1.0f / textureSize.x * (spriteCoords.x + 1);
    BotomRightCoords.y = 1.0f / textureSize.y * (spriteCoords.y + 1);

    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, TopLeftCoords.x,    BotomRightCoords.y,
        1.0f, 0.0f, BotomRightCoords.x, TopLeftCoords.y,
        0.0f, 0.0f, TopLeftCoords.x,    TopLeftCoords.y, 
    
        0.0f, 1.0f, TopLeftCoords.x,    BotomRightCoords.y,
        1.0f, 1.0f, BotomRightCoords.x, BotomRightCoords.y,
        1.0f, 0.0f, BotomRightCoords.x, TopLeftCoords.y
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}   

void SpriteRenderer::Draw()
{
    Shader *spriteShader = RessourceManager::GetShader("Sprite");
    spriteShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f)); 
  
    spriteShader->setMat4("model", model);
    spriteShader->setVec3("spriteColor", color);
  
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, RessourceManager::GetTexture(texture)->getID());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::SetTexture(const std::string &texture)
{
    this->texture = texture;
}

void SpriteRenderer::SetSize(const glm::vec2 &size)
{
    this->size = size;
}