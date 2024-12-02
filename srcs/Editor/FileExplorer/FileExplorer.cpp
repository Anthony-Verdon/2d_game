#include "Editor/FileExplorer/FileExplorer.hpp"
#include <filesystem>
#include "imgui.h"

FileExplorer::FileExplorer()
{
    this->directoryPath = "./";
}

FileExplorer::FileExplorer(const std::string &directoryPath)
{
    this->directoryPath = directoryPath;
}

FileExplorer::~FileExplorer()
{
}

void FileExplorer::Draw()
{
    ImGui::Begin("File Explorer");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::End();
}

void FileExplorer::ReadDirectory(const std::string &directoryPath)
{
    for (auto const& dir_entry : std::filesystem::directory_iterator{directoryPath})
    {
        std::string path = dir_entry.path().string();
        if (std::filesystem::is_directory(path))
            ReadDirectory(path);
    }
}

void FileExplorer::SetDirectoryPath(const std::string &directoryPath)
{
    this->directoryPath = directoryPath;
    ReadDirectory(directoryPath);
}

bool FileExplorer::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}