#pragma once

#include <string>
#include <vector>
#include <memory>

struct Node
{
    std::string data;
    std::vector<std::shared_ptr<Node>> childrens;
};

class FileExplorer
{
    private:
        bool isHoveredOrFocused;

        std::string directoryPath;

        std::shared_ptr<Node> root;

        void ReadDirectory(const std::shared_ptr<Node> &root, const std::string &directoryPath);

    public:
        FileExplorer();
        FileExplorer(const std::string &directoryPath);
        ~FileExplorer();

        void Draw();

        void SetDirectoryPath(const std::string &directoryPath);
        bool IsHoveredOrFocused() const;
};