#pragma once

namespace game::addin {

    /*
    * ISystemProvider provides an interface for system providers.
    */
    class ISystemProvider : public System::ICreator, public SystemConfig::ILoader, public framework::Component::ICreator {
        
        // The aggregated interface

        // virtual SystemConfig* LoadConfig(data::xml::XmlNode root_node) = 0;

        // virtual System* CreateSystem(Engine& engine, SystemConfig& config) = 0;

        // virtual framework::Component* CreateComponent(const string& type_name) = 0;

    };

}