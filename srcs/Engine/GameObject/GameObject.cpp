#include "Engine/GameObject/GameObject.hpp"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(std::unique_ptr<GameObject> component)
{
    childrens.push_back(std::move(component));
}