#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <typeinfo>

//@todo do more class like this, at least for getter/setter
class ATool // @todo could have is own file
{
    private:
        std::string name;
    public:
        ATool() {name = "";}
        ATool(const std::string &name) {this->name = name;}
        virtual ~ATool() {}

        virtual void Load() {}
        virtual void Save() {}

        virtual void Draw() = 0;

        std::string GetName() const {return (name);}
        virtual const void* GetData() const {return(NULL);}
        virtual const std::type_info& GetDataType() const {return (typeid(NULL));}
};

class ToolSelector
{
    private:
        bool isHoveredOrFocused;

        std::unordered_map<std::shared_ptr<ATool>, bool> tools;
        std::unordered_map<std::shared_ptr<ATool>, bool>::iterator toolSelected;

    public:
        ToolSelector();
        ~ToolSelector();

        void Draw();
        
        template <typename T>
        const T* GetData() const
        {
            if (toolSelected == tools.end())
                return (NULL);
            
            if (toolSelected->first->GetDataType() != typeid(T))
                return (NULL);
            
            return (static_cast<const T*>(toolSelected->first->GetData()));
        }

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