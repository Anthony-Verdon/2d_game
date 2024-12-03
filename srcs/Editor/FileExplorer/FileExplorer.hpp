#pragma once

#include <string>
#include <vector>
#include <memory>

struct Node
{
    std::string filename;
    bool isDirectory;
    std::vector<std::shared_ptr<Node>> childrens;
};

class FileExplorer
{
    private:
        bool isHoveredOrFocused;
        std::shared_ptr<Node> root;

        void ReadDirectory(const std::shared_ptr<Node> &root, const std::string &directoryPath);
        void CreateGuiTree(const std::shared_ptr<Node> &root);
    public:
        FileExplorer();
        FileExplorer(const std::string &directoryPath);
        ~FileExplorer();

        void Draw();

        void SetDirectoryPath(const std::string &directoryPath);
        bool IsHoveredOrFocused() const;
};