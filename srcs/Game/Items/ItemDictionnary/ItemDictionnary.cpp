#include "Game/Items/ItemDictionnary/ItemDictionnary.hpp"
#include "Game/Items/ItemBehavior/PickaxeBehavior/PickaxeBehavior.hpp"
#include "Game/Items/ItemBehavior/AxeBehavior/AxeBehavior.hpp"
#include "Game/Items/ItemBehavior/SwordBehavior/SwordBehavior.hpp"
#include "Game/Items/ItemBehavior/HoeBehavior/HoeBehavior.hpp"
#include "Game/Items/ItemBehavior/WateringCanBehavior/WateringCanBehavior.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "globals.hpp"

std::vector<Item> ItemDictionnary::items;

void ItemDictionnary::Init()
{
    RessourceManager::AddTexture("food_icons", "assets/Icons/No Outline/Food_Icons_NO_Outline.png");
    RessourceManager::AddTexture("others_icons", "assets/Icons/No Outline/Other_Icons_NO_Outline.png");
    RessourceManager::AddTexture("ressources_icons", "assets/Icons/No Outline/Resources_Icons_NO_Outline.png");
    RessourceManager::AddTexture("tools_icons", "assets/Icons/No Outline/Tool_Icons_NO_Outline.png");

    AddItems("food_icons", glm::vec2(8, 9), glm::vec2(2, 8));
    AddItems("others_icons", glm::vec2(5, 3), glm::vec2(1, 2));
    AddItems("ressources_icons", glm::vec2(6, 6), glm::vec2(1, 5));
    AddItems("tools_icons", glm::vec2(10, 1), glm::vec2(10, 0));

    items[PICKAXE].behavior = std::make_unique<PickaxeBehavior>();
    items[AXE].behavior = std::make_unique<AxeBehavior>();
    items[SWORD].behavior = std::make_unique<SwordBehavior>();
    items[HOE].behavior = std::make_unique<HoeBehavior>();
    items[WATERING_CAN].behavior = std::make_unique<WateringCanBehavior>();
}

void ItemDictionnary::AddItems(const std::string &textureName, const glm::vec2 &textureSize, const glm::vec2 &spriteStop)
{
    Sprite sprite;
    sprite.size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    sprite.textureName = textureName;
    sprite.textureSize = textureSize;
    for (size_t y = 0; y < sprite.textureSize.y; y++)
    {
        for (size_t x = 0; x < sprite.textureSize.x; x++)
        {
            sprite.spriteCoords = glm::vec2(x, y);
            if (sprite.spriteCoords == spriteStop)
                return;
            Item item = {};
            item.sprite = sprite;
            item.behavior = NULL;
            items.push_back(std::move(item));
        }
    }
}

Sprite ItemDictionnary::GetItemSprite(ItemType item)
{
    return (items[item].sprite);
}

void ItemDictionnary::ExecuteBehavior(ItemType item, const glm::vec2 &position)
{
    if (items[item].behavior != NULL)
        items[item].behavior->MainAction(position);
}