#pragma once

namespace game::framework {

    class GAME_API Component {
        friend class addin::ISystemProvider; 
    protected:

        class ICreator {
        public:
            virtual Component* Create(const string& name, const string& type_name) = 0;
            virtual Component* Create(ComponentConfig& config) = 0;
        };

    private:

        static unordered_map<string, ICreator*>* creators_;

        Engine* engine_;
        System* system_;

        ComponentConfig* config_;

        

    public:

        static void RegisterType(const string& type_name, ICreator* creator);

        static Component* Create(const string& name, const string& type_name);
        static Component* Create(ComponentConfig& config);

    };

}
