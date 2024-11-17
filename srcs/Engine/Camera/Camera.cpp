#include "Engine/Camera/Camera.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "globals.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    position = glm::vec2(0, 0);
}

Camera::~Camera()
{

}

void Camera::SetPosition(const glm::vec2 &position)
{
    this->position = position;
}

void Camera::UpdateShaders() const
{
    float left = position.x - WINDOW_WIDTH / 2;
    float right = position.x + WINDOW_WIDTH / 2;
    float top = position.y - WINDOW_HEIGHT / 2;
    float bottom = position.y + WINDOW_HEIGHT / 2;
    glm::mat4 projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

    std::map<std::string, std::shared_ptr<Shader>> shaders = RessourceManager::GetShaders();
    for (auto it = shaders.begin(); it != shaders.end(); it++)
    {
        it->second->use();
        it->second->setMat4("projection", projection);
    }
}