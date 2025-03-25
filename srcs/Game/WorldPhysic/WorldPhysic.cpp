#include "Game/WorldPhysic/WorldPhysic.hpp"
#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include <glm/glm.hpp>

static void DrawSolidPolygonFcn(b2Transform transform, const b2Vec2* vertices, int verticesCount, float radius, b2HexColor color, void *ctx);
static void DrawSegmentFcn(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void *context);
static void DrawPointFcn(b2Vec2 p, float size, b2HexColor color, void *context);

b2WorldId WorldPhysic::worldId;
float WorldPhysic::timeStep;
int WorldPhysic::subStepCount;
b2DebugDraw WorldPhysic::debugDraw;

void WorldPhysic::Init()
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, 0.0f};
    worldId = b2CreateWorld(&worldDef);
    timeStep = 1.0f / 60.0f;
    subStepCount = 4;

    InitDebugDraw();
    debugDraw.DrawSolidPolygon = DrawSolidPolygonFcn;
    debugDraw.DrawSegment = DrawSegmentFcn;
    debugDraw.DrawPoint = DrawPointFcn;
    debugDraw.drawShapes = true;
}

void WorldPhysic::InitDebugDraw()
{
    debugDraw.context = NULL;
    debugDraw.DrawCapsule = NULL;
    debugDraw.DrawCircle = NULL;
    debugDraw.DrawPoint = NULL;
    debugDraw.DrawPolygon = NULL;
    debugDraw.DrawSegment = NULL;
    debugDraw.DrawSolidCapsule = NULL;
    debugDraw.DrawSolidCircle = NULL;
    debugDraw.DrawSolidPolygon = NULL;
    debugDraw.DrawString = NULL;
    debugDraw.DrawTransform = NULL;

    debugDraw.drawAABBs = false;
    debugDraw.drawContactImpulses = false;
    debugDraw.drawContactNormals = false;
    debugDraw.drawContacts = false;
    debugDraw.drawFrictionImpulses = false;
    debugDraw.drawGraphColors = false;
    debugDraw.drawJointExtras = false;
    debugDraw.drawJoints = false;
    debugDraw.drawMass = false;
    debugDraw.drawShapes = false;
    debugDraw.useDrawingBounds = false;

    float val = 100;
    b2AABB bounds = {{-val, -val}, {val, val}};
    debugDraw.drawingBounds = bounds;
}

static void DrawSolidPolygonFcn(b2Transform transform, const b2Vec2* vertices, int verticesCount, float radius, b2HexColor color, void *ctx) 
{
    (void)ctx;
    (void)radius;
    glm::vec3 newColor = glm::vec3((float)(color & 0xFF0000) / 255, (float)(color & 0x00FF00) / 255, (float)(color & 0x0000FF) / 255);
    float cosAngle = cos(b2Rot_GetAngle(transform.q));
    float sinAngle = sin(b2Rot_GetAngle(transform.q));
    for (int i = 0; i < verticesCount; i++)
    {   
        b2Vec2 b2va = vertices[i];
        b2Vec2 b2vb = vertices[(i + 1) % verticesCount];
        glm::vec2 va = glm::vec2(PhysicBody::WorldToPixel(transform.p.x + b2va.x * cosAngle - b2va.y * sinAngle), PhysicBody::WorldToPixel(transform.p.y + b2va.x * sinAngle + b2va.y * cosAngle));
        glm::vec2 vb = glm::vec2(PhysicBody::WorldToPixel(transform.p.x + b2vb.x * cosAngle - b2vb.y * sinAngle), PhysicBody::WorldToPixel(transform.p.y + b2vb.x * sinAngle + b2vb.y * cosAngle));
        LineRenderer::Draw(va, vb, newColor);
    }
}

static void DrawPointFcn(b2Vec2 p, float size, b2HexColor color, void *context)
{
    (void)p;
    (void)size;
    (void)color;
    (void)context;
}

static void DrawSegmentFcn(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void *context)
{
    (void)context;
    glm::vec2 va = glm::vec2({PhysicBody::WorldToPixel(p1.x), PhysicBody::WorldToPixel(p1.y)}); // @todo WorldToPixel overload taking a glm::vec2 or a b2Vec2 as parameter
    glm::vec2 vb = glm::vec2({PhysicBody::WorldToPixel(p2.x), PhysicBody::WorldToPixel(p2.y)});
    glm::vec3 newColor = glm::vec3((float)(color & 0xFF0000) / 255, (float)(color & 0x00FF00) / 255, (float)(color & 0x0000FF) / 255);
    LineRenderer::Draw(va, vb, newColor);
}