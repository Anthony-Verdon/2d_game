#pragma once

#include <glm/glm.hpp>
#include "Engine/LineRenderer/LineRenderer.hpp"
#include "Engine/GameObject/GameObject.hpp"
#include "Engine/SquareData/SquareData.hpp"

class SquareHitbox: public GameObject, public SquareData
{
    private:
        LineRenderer lineRenderer;

    public:
        SquareHitbox();
        SquareHitbox(const glm::vec2 &coords, const glm::vec2 &size, const glm::vec3 &color);
        ~SquareHitbox();

        bool IsColliding(const SquareHitbox &instance) const;

        void Draw();
};