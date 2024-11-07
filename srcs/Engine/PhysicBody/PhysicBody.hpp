#pragma once

#include <glm/glm.hpp>
class PhysicBody
{
    protected:
        glm::vec2 velocity;
        glm::vec2 force;
        float mass;
        float inversedMass;
        float restitution;
        bool isStatic;
        float inertia;
        float inversedInertia;

        glm::vec2 position;
        float rotation;

        virtual void CalculateInertia();
    public:
        PhysicBody();
        PhysicBody(const glm::vec2 &position, float rotation, float mass, float restitution, bool isStatic);
        ~PhysicBody();

        void Move(const glm::vec2 &amount);
        void Rotate(float amount);
        void AddVelocity(const glm::vec2 amount);
        void AddForce(const glm::vec2 amount);
        
        void SetPosition(const glm::vec2 &position);
        void SetRotation(float rotation);
        void SetMass(float mass);
        void SetRestitution(float restitution);
        void SetStatic(bool isStatic);

        void Step(int iterations);
        virtual glm::vec2 GetPosition() const;
        float GetRotation() const;
        float GetMass() const;
        float GetInversedMass() const;
        float GetRestitution() const;
        glm::vec2 GetVelocity() const;
        bool IsStatic() const;
};