#pragma once

#include <string>
#include <vector>
#include <memory>

struct FileNode
{
    std::string filename;
    bool isDirectory;
    std::vector<std::shared_ptr<FileNode>> childrens;
};

class FileExplorer
{
    private:
        bool isHoveredOrFocused;
        std::shared_ptr<FileNode> root;

        void ReadDirectory(const std::shared_ptr<FileNode> &root, const std::string &directoryPath);
        void CreateGuiTree(const std::shared_ptr<FileNode> &root);
    public:
        FileExplorer();
        FileExplorer(const std::string &directoryPath);
        ~FileExplorer();

        void Draw();

        void SetDirectoryPath(const std::string &directoryPath);
        bool IsHoveredOrFocused() const;
};