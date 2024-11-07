#include "Engine/PolygonRenderer/PolygonRenderer.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

std::unordered_map<std::string, PolygonGl> PolygonRenderer::polygons;
bool PolygonRenderer::isInit = false;

void PolygonRenderer::Init()
{
    if (isInit)
    {
        std::cerr << "PolygonRenderer already initialized" << std::endl;
        return;
    }

    RessourceManager::AddShader("Square", "shaders/square/square.vs", "shaders/square/square.fs");
    isInit = true;
}

void PolygonRenderer::Destroy()
{
    if (!isInit)
    {
        std::cerr << "PolygonRenderer not initialized" << std::endl;
        return;
    }

    for (auto it = polygons.begin(); it != polygons.end(); it++)
    {
        glDeleteVertexArrays(1, &(it->second.VAO));
        glDeleteBuffers(1, &(it->second.EBO));
    }
}

void PolygonRenderer::LoadPolygon(const std::string &polygonName, const std::vector<float> &vertices, const std::vector<int> &faces)
{
    if (!isInit)
    {
        std::cerr << "PolygonRenderer not initialized" << std::endl;
        return;
    }

    if (polygons.find(polygonName) != polygons.end())
    {
        std::cerr << polygonName << " already intialized into PolygonRenderer" << std::endl;
        return;
    }

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                 
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * faces.size(), faces.data(), GL_STATIC_DRAW); 

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);

    PolygonGl newPolygon;
    newPolygon.VAO = VAO;
    newPolygon.EBO = EBO;
    newPolygon.nbFaces = faces.size();
    polygons[polygonName] = newPolygon;
}

void PolygonRenderer::Draw(const std::string &polygonName, const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec3 &color)
{
    if (!isInit)
    {
        std::cerr << "PolygonRenderer not initialized" << std::endl;
        return;
    }

    if (polygons.find(polygonName) == polygons.end())
    {
        std::cerr << polygonName << " not found into PolygonRenderer" << std::endl;
        return;
    }

    Shader *squareShader = RessourceManager::GetShader("Square");
    squareShader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f)); 

    squareShader->setMat4("model", model);
    squareShader->setVec3("color", color);

    PolygonGl polygon = polygons[polygonName];
    glBindVertexArray(polygon.VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, polygon.EBO);
    glDrawElements(GL_TRIANGLES, polygon.nbFaces, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}