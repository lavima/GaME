#pragma once

namespace game::addin {

    /*
    * ISystemProvider provides an interface for system providers.
    */
    class ISystemProvider :
        public framework::System::ICreator,
        public framework::SystemConfig::ILoader {

    };

    class IComponentProvider : 
        public framework::Component::ICreator,
        public framework::ComponentConfig::ICreator {
    };

}