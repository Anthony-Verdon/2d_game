#include "Engine/GameObject/GameObject.hpp"

GameObject::GameObject(): Transform()
{
}

GameObject::GameObject(const glm::vec2 &position, float rotation): Transform(position, rotation)
{
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(std::unique_ptr<GameObject> component)
{
    childrens.push_back(std::move(component));
}