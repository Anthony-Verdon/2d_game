#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

class PhysicBody
{
    private:
        b2BodyId id;

    public:
        PhysicBody();
        PhysicBody(const b2WorldId& worldId, const b2BodyDef& bodyDef, const b2ShapeDef& shapeDef, const b2Polygon& polygon);
        ~PhysicBody();

        b2BodyId GetBodyId() const;
        glm::vec2 GetPosition() const;
        float GetAngle() const;

        static float WorldToPixel(float value);
        static float PixelToWorld(float value);

        class Builder
        {
            private:
                b2BodyDef bodyDef;
                b2Polygon polygon;
                b2ShapeDef shapeDef;
            
            public:
                Builder();
                ~Builder();

                Builder& SetPosition(const glm::vec2 &position);
                Builder& SetType(b2BodyType type);
                Builder& SetSize(const glm::vec2 &size);
                Builder& SetDensity(float density);
                Builder& SetFriction(float friction);

                PhysicBody Build(const b2WorldId &worldId);
        };
};