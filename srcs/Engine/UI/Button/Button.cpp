#include "Engine/UI/Button/Button.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Renderers/PolygonRenderer/PolygonRenderer.hpp"

Button::Button()
{
    for (size_t i = 0; i < 3; i++)
        sprites[i] = Sprite::none;
}
Button::Button(const std::array<Sprite, 3> &sprites)
{
    this->sprites = sprites;
}

Button::~Button()
{
}

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

bool Button::Draw(UIState *ui, size_t ID, const glm::vec2 &position, const glm::vec2 &size)
{
    bool result = false;

    if (IsActive(ui, ID))
    {
        if (!WindowManager::IsInputPressed(GLFW_MOUSE_BUTTON_1)) // not holding anymore
        {
            if (PointInRectangle(WindowManager::GetMousePosition(), position, size)) // still on the button
                result = true;

            SetInactive(ui);
        }
        SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position).SetSize(size).SetSprite(sprites[ButtonAnimation::ACTIVE]).SetDrawAbsolute(true).Build());
    }
    else if (IsHot(ui, ID))
    {
        if (WindowManager::IsInputPressed(GLFW_MOUSE_BUTTON_1))
            SetActive(ui, {ID, ui->globalLayer});
        SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position).SetSize(size).SetSprite(sprites[ButtonAnimation::HOT]).SetDrawAbsolute(true).Build());
    }
    else
    {
        SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position).SetSize(size).SetSprite(sprites[ButtonAnimation::INACTIVE]).SetDrawAbsolute(true).Build());
    }
    
    if (PointInRectangle(WindowManager::GetMousePosition(), position, size))
        SetHot(ui, {ID, ui->globalLayer});

    return (result);
}