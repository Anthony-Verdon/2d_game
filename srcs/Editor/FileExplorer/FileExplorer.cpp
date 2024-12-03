#include "Editor/FileExplorer/FileExplorer.hpp"
#include <filesystem>
#include "imgui.h"

FileExplorer::FileExplorer()
{
    root = std::make_shared<FileNode>();
    root->filename = "./";
    root->isDirectory = true;
}

FileExplorer::FileExplorer(const std::string &directoryPath)
{
    root = std::make_shared<FileNode>();
    root->filename = directoryPath;
    root->isDirectory = true;
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
    
    static std::string textSelected = "";
    ImGui::Text("drop text: %s", textSelected.c_str());
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
        {
            textSelected = *(std::string*)payload->Data;
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::End();
}

void FileExplorer::CreateGuiTree(const std::shared_ptr<FileNode> &root)
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
            ImGui::Selectable(root->childrens[i]->filename.c_str(), false);
            if (ImGui::BeginDragDropSource())
            {
                // Set payload to carry the index of our item (could be anything)
                ImGui::SetDragDropPayload("DND_DEMO_CELL", &root->childrens[i]->filename, sizeof(std::string));
                ImGui::Text("%s", root->childrens[i]->filename.c_str());
                ImGui::EndDragDropSource();
            }
        }
    }
}
void FileExplorer::ReadDirectory(const std::shared_ptr<FileNode> &root, const std::string &directoryPath)
{
    for (auto const& dir_entry : std::filesystem::directory_iterator{directoryPath})
    {
        std::string path = dir_entry.path().string();
        std::string filename = dir_entry.path().filename().string();

        std::shared_ptr<FileNode> child = std::make_shared<FileNode>();
        child->filename = filename;
        child->isDirectory = std::filesystem::is_directory(path);
        root->childrens.push_back(child);

        if (child->isDirectory)
            ReadDirectory(child, path);
    }
}

void FileExplorer::SetDirectoryPath(const std::string &directoryPath)
{
    root->filename = directoryPath;
    root->childrens.clear();
    ReadDirectory(root, directoryPath);
}

bool FileExplorer::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}