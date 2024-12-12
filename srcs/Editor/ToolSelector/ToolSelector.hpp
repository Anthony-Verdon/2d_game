#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>
#include "Editor/ToolSelector/ATool.hpp"

class ToolSelector
{
    private:
        bool isHoveredOrFocused;//@todo: factorize hover and draw function

        std::unordered_map<std::shared_ptr<ATool>, bool> tools;
        std::unordered_map<std::shared_ptr<ATool>, bool>::iterator toolSelected;

    public:
        ToolSelector();
        ~ToolSelector();

        void Draw();
        
        bool IsHoveredOrFocused() const;

        std::shared_ptr<ATool> GetSelectedTool() const;

        template <typename T>
        std::shared_ptr<T> GetTool() const
        {
            for (auto it = tools.begin(); it != tools.end(); it++)
            {
                std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(it->first);
                if (ptr)
                    return (ptr);
            }

            return (NULL);
        }

};