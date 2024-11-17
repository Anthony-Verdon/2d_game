#pragma once

#include <glm/glm.hpp>

class Camera
{
    private:
        glm::vec2 position;

    public:
        Camera();
        ~Camera();

        void SetPosition(const glm::vec2 &position);
        void UpdateShaders() const;
};