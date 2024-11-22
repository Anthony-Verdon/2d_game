#include "Editor/ToolSelector/ToolSelector.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Temporary: public ATool
{
    private:
        int number;

    public:
        Temporary(int number):ATool(std::to_string(number)) {this->number = number;}
        ~Temporary() {}

        void Draw() {ImGui::Text("text from Temporary ! My number is %d", number);}
};

ToolSelector::ToolSelector()
{
    tools.insert({std::make_shared<Temporary>(1), false});
    tools.insert({std::make_shared<Temporary>(2), false});
    tools.insert({std::make_shared<Temporary>(3), false});
}

ToolSelector::~ToolSelector()
{
}

void ToolSelector::Draw()
{
    ImGui::Begin("Tool Selector");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    auto checkboxClicked = tools.end();
    auto toolSelected = tools.end();

    for (auto it = tools.begin(); it != tools.end(); it++)
    {
        ImGui::SameLine();
        if (ImGui::Checkbox(it->first->GetName().c_str(), &it->second))
            checkboxClicked = it;

        if (it->second)
            toolSelected = it;
        
    }

    if (checkboxClicked != tools.end())
    {
        for (auto it = tools.begin(); it != tools.end(); it++)
        {
            if (it != toolSelected)
                it->second = false;
        }
    }

    if (toolSelected != tools.end())
    {
        ImGui::NewLine();
        toolSelected->first->Draw();
    }

    ImGui::End();
}

bool ToolSelector::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}
