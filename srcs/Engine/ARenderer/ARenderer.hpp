#pragma once

#include <glm/glm.hpp>
#include "Engine/GameObject/GameObject.hpp"

enum RendererType
{
    Circle,
    Polygon,
    Line,
    Sprite,
    Count
};

class ARenderer: public GameObject
{
    protected:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        glm::vec3 color;
        RendererType type;

        virtual void Init() = 0;
    public:
        ARenderer(RendererType type);
        ARenderer(const glm::vec3 &color, const glm::vec2 &position, float rotation, float mass, float restitution, bool isStatic, RendererType type);
        virtual ~ARenderer();

        virtual void Draw() = 0;
        void SetColor(const glm::vec3 &color);
        glm::vec3 GetColor() const;
        RendererType GetType() const;
        
        
};