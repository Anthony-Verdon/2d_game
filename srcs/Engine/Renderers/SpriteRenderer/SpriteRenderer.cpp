#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

unsigned int SpriteRenderer::VAO = -1;
unsigned int SpriteRenderer::VBO = -1;
bool SpriteRenderer::isInit = false;

void SpriteRenderer::Init(unsigned int width, unsigned int height)
{
    if (isInit)
    {
        std::cerr << "SpriteRenderer already initialized" << std::endl;
        return;
    }

    RessourceManager::AddShader("Sprite", "shaders/sprite/sprite.vs", "shaders/sprite/sprite.fs");
    std::shared_ptr<Shader> spriteShader = RessourceManager::GetShader("Sprite");
    spriteShader->use();
    spriteShader->setInt("image", 0);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    spriteShader->setMat4("projection", projection);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    float positions[] = { 
        -0.5f, 0.5f, 
        0.5f, -0.5f, 
       -0.5f, -0.5f, 
    
        -0.5f, 0.5f, 
        0.5f, 0.5f, 
        0.5f, -0.5f
    };

    float textures[] = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f, 

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(textures), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(textures), textures);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)sizeof(positions));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);

    isInit = true;
}

void SpriteRenderer::Destroy()
{
    if (!isInit)
    {
        std::cerr << "SpriteRenderer not initialized" << std::endl;
        return;
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void SpriteRenderer::Draw(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec3 &color, const Sprite &sprite, bool flipHorizontally, bool flipVertically)
{
    if (!isInit)
    {
        std::cerr << "SpriteRenderer not initialized" << std::endl;
        return;
    }

    glm::vec2 TopLeftCoords;
    glm::vec2 BotomRightCoords;
    TopLeftCoords.x = 1.0f / sprite.textureSize.x * sprite.spriteCoords.x;
    TopLeftCoords.y = 1.0f / sprite.textureSize.y * sprite.spriteCoords.y;
    BotomRightCoords.x = 1.0f / sprite.textureSize.x * (sprite.spriteCoords.x + 1);
    BotomRightCoords.y = 1.0f / sprite.textureSize.y * (sprite.spriteCoords.y + 1);

    if (flipHorizontally)
        std::swap(TopLeftCoords.x, BotomRightCoords.x);
    if (flipVertically)
        std::swap(TopLeftCoords.y, BotomRightCoords.y);

    float positions[] = { 
        -0.5f, 0.5f, 
        0.5f, -0.5f, 
       -0.5f, -0.5f, 
    
        -0.5f, 0.5f, 
        0.5f, 0.5f, 
        0.5f, -0.5f
    };

    float textures[] = {
        TopLeftCoords.x,    BotomRightCoords.y,
        BotomRightCoords.x, TopLeftCoords.y,
        TopLeftCoords.x,    TopLeftCoords.y, 

        TopLeftCoords.x,    BotomRightCoords.y,
        BotomRightCoords.x, BotomRightCoords.y,
        BotomRightCoords.x, TopLeftCoords.y
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(textures), textures);

    std::shared_ptr<Shader> spriteShader = RessourceManager::GetShader("Sprite");
    spriteShader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::scale(model, glm::vec3(size, 1.0f)); 
  
    spriteShader->setMat4("model", model);
    spriteShader->setVec3("spriteColor", color);
  
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, RessourceManager::GetTexture(sprite.textureName)->getID());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}