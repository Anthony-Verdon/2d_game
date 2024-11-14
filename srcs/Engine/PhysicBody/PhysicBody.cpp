#include "Engine/PhysicBody/PhysicBody.hpp"
#include <iostream>
#include "globals.hpp"

PhysicBody::PhysicBody()
{
    
}

PhysicBody::PhysicBody(const b2WorldId& worldId, const b2BodyDef& bodyDef, const b2ShapeDef& shapeDef, const b2Polygon& polygon)
{
    id = b2CreateBody(worldId, &bodyDef);
    b2CreatePolygonShape(id, &shapeDef, &polygon);
    {
        b2ShapeDef newShapeDef = b2DefaultShapeDef();
        newShapeDef.isSensor = true;

        b2Vec2 points[4];
        int size = 16;
        points[0] = {PixelToWorld(-size), PixelToWorld(-size)};
        points[1] = {PixelToWorld(size), PixelToWorld(-size)};
        points[2] = {PixelToWorld(size), PixelToWorld(size)};
        points[3] = {PixelToWorld(-size), PixelToWorld(size)};
        b2Hull hull = b2ComputeHull(points, 4);

        b2Transform transform;
        transform.p = (b2Vec2){PixelToWorld(32 * 2), 0};
        transform.q = b2MakeRot(glm::radians(0.0f));

        b2Polygon offsetPolygon = b2MakeOffsetPolygon(&hull, 0, transform);
    
        b2CreatePolygonShape(id, &newShapeDef, &offsetPolygon);
    }
}

PhysicBody::~PhysicBody()
{

}

float PhysicBody::WorldToPixel(float value)
{
    return (value * PIXEL_PER_METER);
}

float PhysicBody::PixelToWorld(float value)
{
    return (value / PIXEL_PER_METER);
}

b2BodyId PhysicBody::GetBodyId() const
{
    return (id);
}

glm::vec2 PhysicBody::GetPosition() const
{
    b2Vec2 worldPosition = b2Body_GetPosition(id);
    return (glm::vec2(WorldToPixel(worldPosition.x), WorldToPixel(worldPosition.y)));
}

float PhysicBody::GetAngle() const
{
    return (glm::degrees(b2Rot_GetAngle(b2Body_GetRotation(id))));
}

PhysicBody::Builder::Builder()
{
    bodyDef = b2DefaultBodyDef();
    shapeDef = b2DefaultShapeDef();
}

PhysicBody::Builder::~Builder()
{

}

PhysicBody::Builder& PhysicBody::Builder::SetPosition(const glm::vec2 &position)
{
    bodyDef.position = (b2Vec2){PixelToWorld(position.x), PixelToWorld(position.y)};
    return (*this);
}

PhysicBody::Builder& PhysicBody::Builder::SetEnable(bool enable)
{
    bodyDef.isEnabled = enable;
    return (*this);
}

PhysicBody::Builder& PhysicBody::Builder::SetType(b2BodyType type)
{
    bodyDef.type = type;
    return (*this);
}

PhysicBody::Builder& PhysicBody::Builder::SetFixedRotation(bool fixedRotation)
{
    bodyDef.fixedRotation = fixedRotation;
    return (*this);
}

PhysicBody::Builder &PhysicBody::Builder::SetSize(const glm::vec2 &size)
{
    polygon = b2MakeBox(PixelToWorld(size.x / 2), PixelToWorld(size.y / 2));
    return (*this);
}

PhysicBody::Builder& PhysicBody::Builder::SetDensity(float density)
{
    shapeDef.density = density;
    return (*this);
}

PhysicBody::Builder& PhysicBody::Builder::SetFriction(float friction)
{
    shapeDef.friction = friction;
    return (*this);
}

PhysicBody::Builder& PhysicBody::Builder::SetFilter(const b2Filter &filter)
{
    shapeDef.filter = filter;
    return (*this);
}

PhysicBody PhysicBody::Builder::Build(const b2WorldId &worldId)
{
    return (PhysicBody(worldId, bodyDef, shapeDef, polygon));
}