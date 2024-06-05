#pragma once

#include "ComponentType.hpp"
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace Engine
{
    class Component
    {
    public:
        Component(ComponentType type);
        virtual ~Component();

        ComponentType get_type() const;
        virtual void read_in(json data) = 0;
    private:
        ComponentType m_type;
    };

    class ComponentCreator // Functinoid
    {
    public:
        ComponentCreator();
        virtual ~ComponentCreator(){};
        virtual std::shared_ptr<Component> create() = 0;
    protected:
    };
} // namespace Engine
