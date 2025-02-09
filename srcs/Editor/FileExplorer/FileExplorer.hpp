#pragma once

#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include "Editor/AEditorWindow/AEditorWindow.hpp"

struct FileNode
{
    std::string filename;
    std::string path;
    bool isDirectory;
    std::vector<std::shared_ptr<FileNode>> childrens;
};

class FileExplorer: public AEditorWindow
{
    private:
        std::shared_ptr<FileNode> root;
        std::filesystem::file_time_type lastTimeModified;

        void ReadDirectory(const std::shared_ptr<FileNode> &root, const std::string &directoryPath);
        void CreateGuiTree(const std::shared_ptr<FileNode> &root);
    public:
        FileExplorer();
        FileExplorer(const std::string &directoryPath);
        ~FileExplorer();

        void Draw();

        void SetDirectoryPath(const std::string &directoryPath);
};