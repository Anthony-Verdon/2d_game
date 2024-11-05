#include "Engine/GameObject/GameObject.hpp"

GameObject::GameObject(): PhysicBody()
{
}

GameObject::GameObject(const glm::vec2 &position, float rotation): PhysicBody(position, rotation)
{
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(std::unique_ptr<GameObject> component)
{
    childrens.push_back(std::move(component));
}