#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Engine/PhysicBody/PhysicBody.hpp"

class GameObject: public PhysicBody
{
    protected:
        std::vector<std::unique_ptr<GameObject>> childrens;

    public:
        GameObject();
        GameObject(const glm::vec2 &position, float rotation, float mass, float restitution, bool isStatic);
        virtual ~GameObject();

        template <typename T>
        T* GetComponent() const
        {
            for (const auto &object: childrens)
            {
                T* ptr = dynamic_cast<T*>(object.get());
                if (ptr)
                    return (ptr);
            }
            return (nullptr);
        }

        void AddComponent(std::unique_ptr<GameObject> component);
};