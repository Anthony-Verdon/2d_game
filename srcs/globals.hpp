#pragma once

//@todo separate this file

//#define FULL_SCREEN
// window
#ifdef FULL_SCREEN
constexpr int WINDOW_WIDTH = 1920;
constexpr int WINDOW_HEIGHT = 1080;
#else
constexpr int WINDOW_WIDTH = 1080;
constexpr int WINDOW_HEIGHT = 720;
#endif

// box2d
constexpr float PIXEL_PER_METER = 50;

// sprite
constexpr float TILE_SIZE = 16;
constexpr float SCALE_FACTOR = 4;
constexpr float SPRITE_SIZE = TILE_SIZE * SCALE_FACTOR;

// UI
constexpr float SLOT_SIZE = TILE_SIZE * 2.0f;

// editor
constexpr float CHAIN_POINT_RADIUS = 10;
constexpr int INPUT_ARRAY_SIZE = 100;

// loot
constexpr float LOOT_SPEED = 10;
constexpr float PLAYER_LOOT_RADIUS = 100;
constexpr float PLAYER_CLOSE_LOOT_RADIUS = 10;

// inventory
constexpr int INVENTORY_WIDTH = 6;
constexpr int INVENTORY_BAR_HEIGHT = 1;
constexpr int INVENTORY_EXPANDED_HEIGHT = 4;
constexpr int INVENTORY_HEIGHT = INVENTORY_BAR_HEIGHT + INVENTORY_EXPANDED_HEIGHT;
constexpr int INVENTORY_SIZE = INVENTORY_WIDTH * INVENTORY_HEIGHT;

