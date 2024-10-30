#pragma once

#include <glm/glm.hpp>

class LineData
{
    protected:
        glm::vec2 start;
        glm::vec2 end;
        glm::vec3 color;
    
    public:
        LineData();
        LineData(const glm::vec2 &start, const glm::vec2 &end,const glm::vec3 &color);
        ~LineData();

        void SetStart(const glm::vec2 &start);
        void SetEnd(const glm::vec2 &end);
        void SetColor(const glm::vec3 &color);

        glm::vec2 GetStart() const;
        glm::vec2 GetEnd() const;
        glm::vec3 GetColor() const;
};