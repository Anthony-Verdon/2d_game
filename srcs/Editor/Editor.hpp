#pragma once

#include "Engine/AProgram/AProgram.hpp"
#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Camera/Camera.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <Box2D/Box2D.h>

#include <string>
#include <vector>

struct TextureData
{
    std::string name;
    glm::vec2 size;

};
class Editor: public AProgram
{
    private:
        Tilemap tilemap;
        Camera camera;
        Sprite actualSprite;
        bool ImGuiWindowHoweredOrFocused;
        std::vector<TextureData> texturesData;
        
        b2WorldId worldId;
        float timeStep;
        int subStepCount;
        b2DebugDraw debugDraw;
        void InitDebugDraw();

        void CreateTileSelector();
        void ProcessInput();
        void UpdateCamera();
        void UpdateTilemap();

        void Draw();
    public:
        Editor();
        ~Editor();

        void Run();

        void ScrollCallback(double xOffset, double yOffset);
};