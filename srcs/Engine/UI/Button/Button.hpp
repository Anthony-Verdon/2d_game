#pragma once

#include <glm/glm.hpp>

struct UIID
{
    size_t ID;
    size_t layer;
};

struct UIElement
{
    UIID ID;
    glm::vec2 rectPosition;
    glm::vec2 rectSize;
};

struct UIState
{
    UIID active;
    UIID hotThisFrame;
    UIID hotLastFrame;

    size_t globalLayer;
};

class Button
{
    private:
        static void SetHot(UIState* ui, UIID uiID);
        static void SetActive(UIState* ui, UIID uiID) { ui->active = uiID; }
        static void SetInactive(UIState* ui) { ui->active = {}; }

        static bool IsHot(UIState* ui, size_t ID) { return (ui->hotLastFrame.ID > 0 && ui->hotLastFrame.ID == ID); }
        static bool IsActive(UIState* ui, size_t ID) { return (ui->active.ID > 0 && ui->active.ID == ID); }
        static bool PointInRectangle(const glm::vec2 &mousePosition, const glm::vec2 &rectPosition, const glm::vec2 &rectSize);

        Button() = delete;
        ~Button() = delete;

    public:
        static bool Draw(UIState *ui, size_t ID, const glm::vec2 &rectPosition, const glm::vec2 &rectSize, const glm::vec2 &topLeftCorner);
};