#pragma once

class AEditorWindow
{
    protected:
        bool isHoveredOrFocused;
    
    public:
        AEditorWindow() {}
        virtual ~AEditorWindow() {}

        virtual void Draw() = 0;

        bool IsHoveredOrFocused() const { return isHoveredOrFocused; }
};
