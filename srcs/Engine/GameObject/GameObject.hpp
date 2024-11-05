#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Engine/Transform/Transform.hpp"

class GameObject: public Transform
{
    protected:
        std::vector<std::unique_ptr<GameObject>> childrens;

    public:
        GameObject();
        GameObject(const glm::vec2 &position, float rotation);
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