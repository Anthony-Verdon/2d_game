#include "Engine/UI/Button/Button.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Renderers/PolygonRenderer/PolygonRenderer.hpp"

void Button::SetHot(UIState* ui, UIID uiID)
{
    if (!(ui->active.ID > 0) && uiID.layer >= ui->hotThisFrame.layer)
        ui->hotThisFrame = uiID;
}

bool Button::PointInRectangle(const glm::vec2 &mousePosition, const glm::vec2 &rectPosition, const glm::vec2 &rectSize)
{
    glm::vec2 HalftRectSize = rectSize / 2.0f;
    return (mousePosition.x >= rectPosition.x - HalftRectSize.x
        && mousePosition.y >= rectPosition.y - HalftRectSize.x
        && mousePosition.x <= rectPosition.x + HalftRectSize.x 
        && mousePosition.y <= rectPosition.y + HalftRectSize.y);
}

// hot = hovering
// active = clicked + holding
// inactive = !hot && !active
bool Button::Draw(UIState *ui, size_t ID, const glm::vec2 &rectPosition, const glm::vec2 &rectSize, const glm::vec2 &topLeftCorner)
{
    bool result = false;

    UIElement element;
    element.ID = {ID, ui->globalLayer};
    element.rectPosition = rectPosition;
    element.rectSize = rectSize;

    if (IsActive(ui, ID))
    {
        if (!WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) // not holding anymore
        {
            if (PointInRectangle(topLeftCorner + WindowManager::GetMousePosition(), element.rectPosition, element.rectSize)) // still on the button
                result = true;

            SetInactive(ui);
        }
        PolygonRenderer::Draw("square", element.rectPosition, element.rectSize, 0, glm::vec3(0, 1, 0));
    }
    else if (IsHot(ui, ID))
    {
        if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
            SetActive(ui, element.ID);
        PolygonRenderer::Draw("square", element.rectPosition, element.rectSize, 0, glm::vec3(1, 0, 0));
    }
    else
    {
        PolygonRenderer::Draw("square", element.rectPosition, element.rectSize, 0, glm::vec3(0, 0, 1));
    }
    
    if (PointInRectangle(topLeftCorner + WindowManager::GetMousePosition(), element.rectPosition, element.rectSize))
        SetHot(ui, element.ID);

    return (result);
}