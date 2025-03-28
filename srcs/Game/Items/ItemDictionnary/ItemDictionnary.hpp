#pragma once

#include <vector>
#include "Engine/2D/Sprite/Sprite.hpp"
#include "Game/Items/ItemBehavior/AItemBehavior/AItemBehavior.hpp"
#include <memory>

enum ItemType
{
    // food
    RAW_CHICKEN = 0,
    COOKED_CHICKEN,
    RAW_PIG,
    COOKED_PIG,
    BROWN_MUSHROOM,
    PURPLE_MUSHROOM,
    HONEY,
    MILK,
    RAW_COW,
    COOKED_COW,
    RAW_SHEEP,
    COOKED_SHEEP,
    RED_MUSHROOM,
    BLUE_MUSHROOM,
    RAW_EGG,
    COOKED_EGG,
    BLUE_FISH,
    CYAN_FISH,
    DARK_BLUE_FISH,
    GREEN_FISH,
    BROWN_FISH,
    RED_FISH,
    ORANGE_FISH,
    GREY_FISH,
    WHEAT,
    WHEAT_SEED,
    WATERMELON,
    WATERMON_SEED,
    RED_BELL_PEPPER,
    RED_BELL_PEPPER_SEED,
    APPLE,
    APPLE_SEED,
    TOMATO,
    TOMATO_SEED,
    CARROT,
    CARROT_SEED,
    YELLOW_BELL_PEPPER,
    YELLOW_BELL_PEPPER_SEED,
    PEACH,
    PEACH_SEED,
    GRAPE,
    GRAPE_SEED,
    SALAD,
    SALAD_SEED,
    GREEN_BELL_PEPPER,
    GREEN_BELL_PEPPER_SEED,
    PEAR,
    PEAR_SEED,
    PUMPKIN,
    PUMPKIN_SEED,
    CUCUMBER,
    CUCUMBER_SEED,
    CHILI_PEPPER,
    CHILI_PEPPER_SEED,
    CHERRY,
    CHERRY_SEED,
    CORN,
    CORN_SEED,
    PARSNIP,
    PARSNIP_SEED,
    RADISH,
    RADISH_SEED,
    WATERMELON_SLICE,
    HONEY_FLASK,
    STRAWBERRY,
    BLUEBERRY,
    // others
    RED_FLOWER,
    MAGENTA_FLOWER,
    PINK_FLOWER,
    DARK_MAGENTA_FLOWER,
    VIOLET_FLOWER,
    CYAN_FLOWER,
    ORANGE_FLOWER,
    YELLOW_FLOWER,
    GREEN_FLOWER,
    BLUE_FLOWER,
    FLOWER_POT,
    // ressources
    IRON_NUGGET,
    IRON_ORE,
    IRON_INGOT,
    BLUE_NUGGET,
    BLUE_ORE,
    BLUE_INGOT,
    COPPER_NUGGET,
    COPPER_ORE,
    COPPER_INGOT,
    ORANGE_NUGGET,
    ORANGE_ORE,
    ORANGE_INGOT,
    GOLD_NUGGET,
    GOLD_ORE,
    GOLD_INGOT,
    RED_NUGGET,
    RED_ORE,
    RED_INGOT,
    EMERAUD_NUGGET,
    EMERAUD_ORE,
    EMERAUD_INGOT,
    AMETHYST_NUGGET,
    AMETHYST_ORE,
    AMETHYST_INGOT,
    WOOD,
    BONE,
    WOOD_STICK,
    LEAF,
    WOOD_BARK,
    PEARL,
    STONE,
    // tools
    BOW,
    ARROW,
    PICKAXE,
    AXE,
    SWORD,
    HOE,
    WATERING_CAN,
    FISHING_ROD,
    LANTERN,
    TORCH,
    // none
    NONE
};

struct Item
{
    Sprite sprite;
    std::unique_ptr<AItemBehavior> behavior;
};

class ItemDictionnary
{
    private:
        ItemDictionnary() = delete;
        ~ItemDictionnary() = delete;

        static std::vector<Item> items;

        static void AddItems(const std::string &textureName, const glm::vec2 &textureSize, const glm::vec2 &spriteStop);
    
    public:
        static void Init();
        static Sprite GetItemSprite(ItemType item);
        static void ExecuteBehavior(ItemType item, const glm::vec2 &position = glm::vec2(0, 0));

};