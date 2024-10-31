#pragma once

#include <glm/glm.hpp>
class Transform
{
    protected:
        glm::vec2 position;
        float rotation;

    public:
        Transform();
        Transform(const glm::vec2 &position, float rotation);
        ~Transform();

        void Move(const glm::vec2 &amount);
        
        void SetPosition(const glm::vec2 &position);
        void SetRotation(float rotation);

        glm::vec2 GetPosition() const;
        float GetRotation() const;
};