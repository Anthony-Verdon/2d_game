#pragma once

#include <glm/glm.hpp>
class Transform
{
    protected:
        glm::vec2 velocity;
        glm::vec2 force;
        glm::vec2 position;
        float rotation;

    public:
        Transform();
        Transform(const glm::vec2 &position, float rotation);
        ~Transform();

        void Move(const glm::vec2 &amount);
        void Rotate(float amount);
        void AddVelocity(const glm::vec2 amount);
        void AddForce(const glm::vec2 amount);
        
        void SetPosition(const glm::vec2 &position);
        void SetRotation(float rotation);

        void Step();
        glm::vec2 GetPosition() const;
        float GetRotation() const;
        glm::vec2 GetVelocity() const;
};