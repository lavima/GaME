#pragma once

namespace game::framework {

    enum class ComponentStatus {
        Created,
        Initialized,
        Destroyed
    };

    class Entity;

    class GAME_API Component {
        friend class addin::IComponentProvider;
    protected:

        class ICreator {
        public:
            virtual Component* Create(Entity& entity, ComponentConfig& config) = 0;
        };

    private:

        static std::unordered_map<std::string, ICreator*>* creators_;

        Entity* entity_;

        ComponentStatus status_; 

        ComponentConfig* config_;

    protected:
        
        /*
        * Creates a new component. The config object is created and pushed to the
        * parent entity specification.
        */
        Component(Entity& entity, const std::string& name, const std::string& type_name);

        /*
        *   Format a new component. 
        */
        Component(Entity& entity, ComponentConfig& config, bool store_config_in_entity=false);

    public:

        virtual ~Component();

        static void RegisterType(const std::string& type_name, ICreator* creator);
        

        static Component* Create(Entity& entity, const std::string& name, const std::string& type_name);
        static Component* Create(Entity& entity, ComponentConfig& config);


        virtual bool Initialize();
        virtual void Update(const GameTime& game_time) = 0;
        virtual void Destroy();

        Entity& GetEntity() const;
        ComponentStatus GetStatus() const;
        ComponentConfig& GetConfig();
    

    };

}
