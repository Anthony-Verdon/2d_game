#pragma once

class FileExplorer
{
    private:
        bool isHoveredOrFocused;
        
    public:
        FileExplorer();
        ~FileExplorer();

        void Draw();

        bool IsHoveredOrFocused() const;
};