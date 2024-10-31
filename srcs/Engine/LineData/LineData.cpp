#include "Engine/LineData/LineData.hpp"

LineData::LineData()
{
    start = glm::vec2(0, 0);
    end = glm::vec2(0, 0);
}

LineData::LineData(const glm::vec2 &start, const glm::vec2 &end)
{
    this->start = start;
    this->end = end;
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

glm::vec2 LineData::GetStart() const
{
    return (start);
}

glm::vec2 LineData::GetEnd() const
{
    return (end);
}