#pragma once

#include <glm/glm.hpp>

class LineData
{
    protected:
        glm::vec2 start;
        glm::vec2 end;
    
    public:
        LineData();
        LineData(const glm::vec2 &start, const glm::vec2 &end);
        ~LineData();

        void SetStart(const glm::vec2 &start);
        void SetEnd(const glm::vec2 &end);

        glm::vec2 GetStart() const;
        glm::vec2 GetEnd() const;
};