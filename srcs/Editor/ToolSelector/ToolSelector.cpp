#include "Editor/ToolSelector/ToolSelector.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Temporary: public ATool
{
    private:
        int number;

    public:
        Temporary(int number) {this->number = number;}
        ~Temporary() {}

        void Draw() {ImGui::Text("text from Temporary ! My number is %d", number);}
};

ATool::ATool()
{
}

ATool::~ATool()
{
}

ToolSelector::ToolSelector()
{
    tools.insert({"Chain Builder", std::pair<bool, std::shared_ptr<ATool>>(false, std::make_shared<Temporary>(1))});
    tools.insert({"Tile Selector", std::pair<bool, std::shared_ptr<ATool>>(false, std::make_shared<Temporary>(2))});
    tools.insert({"Third tool", std::pair<bool, std::shared_ptr<ATool>>(false, std::make_shared<Temporary>(3))});
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
        if (ImGui::Checkbox(it->first.c_str(), &it->second.first))
            checkboxClicked = it;

        if (it->second.first)
            toolSelected = it;
        
    }

    if (checkboxClicked != tools.end())
    {
        for (auto it = tools.begin(); it != tools.end(); it++)
        {
            if (it != toolSelected)
                it->second.first = false;
        }
    }

    if (toolSelected != tools.end())
    {
        ImGui::NewLine();
        toolSelected->second.second->Draw();
    }

    ImGui::End();
}

bool ToolSelector::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}
