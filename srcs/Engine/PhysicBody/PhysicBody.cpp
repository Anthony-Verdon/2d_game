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
}

PhysicBody::~PhysicBody()
{

}

float PhysicBody::WorldToPixel(float value)
{
    return (value * pixelPerMeter);
}

float PhysicBody::PixelToWorld(float value)
{
    return (value / pixelPerMeter);
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

PhysicBody::Builder& PhysicBody::Builder::SetType(b2BodyType type)
{
    bodyDef.type = type;
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

PhysicBody PhysicBody::Builder::Build(const b2WorldId &worldId)
{
    return (PhysicBody(worldId, bodyDef, shapeDef, polygon));
}