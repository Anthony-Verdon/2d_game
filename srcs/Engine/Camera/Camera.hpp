#pragma once

#include <glm/glm.hpp>

class Camera
{
    private:
        glm::vec2 position;
        float zoom;

    public:
        Camera();
        ~Camera();

        void SetPosition(const glm::vec2 &position);
        glm::vec2 GetPosition() const;
        void Zoom(float amount);
        void UpdateShaders() const;
};