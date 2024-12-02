#pragma once

#include <string>

class FileExplorer
{
    private:
        bool isHoveredOrFocused;

        std::string directoryPath;

        void ReadDirectory(const std::string &directoryPath);

    public:
        FileExplorer();
        FileExplorer(const std::string &directoryPath);
        ~FileExplorer();

        void Draw();

        void SetDirectoryPath(const std::string &directoryPath);
        bool IsHoveredOrFocused() const;
};