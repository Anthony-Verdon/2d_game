#pragma once


#include "Game/ItemDictionnary/ItemDictionnary.hpp"

class Player;

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

class InventoryBar
{
    private:
        glm::vec2 slotSelected;
        glm::vec2 topLeftCorner;

        void DrawInventorySlotBackground(const glm::vec2 &position, const glm::vec2 &size);
        void DrawMultipleSlots(const glm::vec2 &position, const glm::vec2 &backgroundSize, const glm::vec2 &nbSlot, bool gapOnEdge);
        void DrawInventorySlot(const glm::vec2 &position, Items item, bool isSelected);
        int DetermineSpriteCoord(int coord, int size);
        bool DrawButton(UIState *ui, size_t ID, const glm::vec2 &rectPosition, const glm::vec2 &rectSize);

        UIState state;
    public:
        InventoryBar();
        ~InventoryBar();

        void SetSlotSelected(const glm::vec2 &slotSelected) {this->slotSelected = slotSelected;}
        void Draw(const Player &player);
};