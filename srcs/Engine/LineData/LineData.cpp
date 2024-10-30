#include "Engine/LineData/LineData.hpp"

LineData::LineData()
{
    start = glm::vec2(0, 0);
    end = glm::vec2(0, 0);
    color = glm::vec3(0, 0, 0);
}

LineData::LineData(const glm::vec2 &start, const glm::vec2 &end,const glm::vec3 &color)
{
    this->start = start;
    this->end = end;
    this->color = color;
}

LineData::~LineData()
{

}

void LineData::SetStart(const glm::vec2 &start)
{
    this->start = start;
}

void LineData::SetEnd(const glm::vec2 &end)
{
    this->end = end;
}

void LineData::SetColor(const glm::vec3 &color)
{
    this->color = color;
}

glm::vec2 LineData::GetStart() const
{
    return (start);
}

glm::vec2 LineData::GetEnd() const
{
    return (end);
}

glm::vec3 LineData::GetColor() const
{
    return (color);
}
