#include "Engine/PolygonBody/PolygonBody.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

PolygonBody::PolygonBody(): ARenderer(RendererType::Polygon)
{
    size = glm::vec2(10, 10);
    CalculateInertia();
    Init();
}

PolygonBody::PolygonBody(const std::vector<float> &vertices, const std::vector<int> &faces, const glm::vec2 &position, float rotation, const glm::vec2 &size, const glm::vec3 &color, float mass, float restitution, bool isStatic): ARenderer(color, position, rotation, mass, restitution, isStatic, RendererType::Polygon)
{
    this->size = size;
    this->vertices = vertices;
    this->faces = faces;
    CalculateInertia();
    Init();
}

PolygonBody::~PolygonBody()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
}

void PolygonBody::Init()
{
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
    
}

void PolygonBody::Draw()
{
    Shader *squareShader = RessourceManager::GetShader("Square");
    squareShader->use();
    squareShader->setMat4("model", CalculateModelMatrix());
    squareShader->setVec3("color", color);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::mat4 PolygonBody::CalculateModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f)); 

    return (model);
}

void PolygonBody::SetSize(const glm::vec2 &size)
{
    this->size = size;
}

glm::vec2 PolygonBody::GetSize() const
{
    return (size);
}

float PolygonBody::GetWidth() const
{
    return (size.x);
}

float PolygonBody::GetHeight() const
{
    return (size.y);
}

std::vector<glm::vec2> PolygonBody::CalculateVerticesPosition() const
{
    glm::mat4 model = CalculateModelMatrix();

    std::vector<glm::vec2> verticesMoved;
    for (unsigned int i = 0; i < vertices.size(); i += 2)
    {
        glm::vec4 tmp = glm::vec4(vertices[i], vertices[i + 1], 0, 1);
        tmp = model * tmp;
        verticesMoved.push_back(glm::vec2(tmp.x, tmp.y));
    }

    return (verticesMoved);
}

void PolygonBody::CalculateInertia()
{
    // formula for square
    inertia = 1.0f / 12.0f * mass * (size.x * size.x + size.y * size.y);
    if (isStatic)
        inversedInertia = 0;
    else
        inversedInertia = 1 / inertia;
}

glm::vec2 PolygonBody::GetPosition() const
{
    return (position + size / 2.0f);
}