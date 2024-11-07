#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>
#include <vector>

struct PolygonGl
{
    unsigned int VAO;
    unsigned int EBO;
    unsigned int nbFaces;
};

class PolygonRenderer
{
    private:
        static std::unordered_map<std::string, PolygonGl> polygons;
        static bool isInit;

        PolygonRenderer() = delete;
        ~PolygonRenderer() = delete;
    public: 
        static void Init(unsigned int width, unsigned int height);
        static void Destroy();
        static void LoadPolygon(const std::string &polygonName, const std::vector<float> &vertices, const std::vector<int> &faces);
        static void Draw(const std::string &polygonName, const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec3 &color);
};