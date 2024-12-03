#include "Editor/FileExplorer/FileExplorer.hpp"
#include <filesystem>
#include "imgui.h"

FileExplorer::FileExplorer()
{
    this->directoryPath = "./";
    root = std::make_shared<Node>();
}

FileExplorer::FileExplorer(const std::string &directoryPath)
{
    this->directoryPath = directoryPath;
    root = std::make_shared<Node>();
}

FileExplorer::~FileExplorer()
{
}

void FileExplorer::Draw()
{
    ImGui::Begin("File Explorer");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::Text("directory: %s", root->filename.c_str());
    CreateGuiTree(root);

    ImGui::End();
}

void FileExplorer::CreateGuiTree(const std::shared_ptr<Node> &root)
{
    for (size_t i = 0; i < root->childrens.size(); i++)
    {
        if (root->childrens[i]->isDirectory)
        {
            if (ImGui::TreeNode(root->childrens[i]->filename.c_str()))
            {
                CreateGuiTree(root->childrens[i]);
                ImGui::TreePop();
            }
        }
        else
        {
            ImGui::Text("%s", root->childrens[i]->filename.c_str());
        }
    }
}
void FileExplorer::ReadDirectory(const std::shared_ptr<Node> &root, const std::string &directoryPath)
{
    for (auto const& dir_entry : std::filesystem::directory_iterator{directoryPath})
    {
        std::string path = dir_entry.path().string();
        std::string filename = dir_entry.path().filename().string();

        std::shared_ptr<Node> child = std::make_shared<Node>();
        child->filename = filename;
        child->isDirectory = std::filesystem::is_directory(path);
        root->childrens.push_back(child);

        if (child->isDirectory)
            ReadDirectory(child, path);
    }
}

void FileExplorer::SetDirectoryPath(const std::string &directoryPath)
{
    this->directoryPath = directoryPath;
    root->filename = directoryPath;
    root->isDirectory = true;
    root->childrens.clear();
    ReadDirectory(root, directoryPath);
}

bool FileExplorer::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}