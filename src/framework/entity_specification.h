#pragma once

namespace game::framework {

#define EXTENSION_ENTITY "entity"

#define XMLNAME_ENTITY "Entity"
#define XMLNAME_ENTITY_NAME "Name"
#define XMLNAME_ENTITY_DESCRIPTION "Description"
#define XMLNAME_ENTITY_COMPONENT "Component"

    class EntitySpecification : public content::XmlContent {
        friend class Entity;
    private:

        std::string name_;
        std::string description_;

        std::vector<std::unique_ptr<ComponentConfig>> components_;
        
        EntitySpecification(const std::string& name, const std::string& description);
        EntitySpecification(const std::string& filename);

    public:

        virtual ~EntitySpecification();
        
        static EntitySpecification* Create(const std::string& name, const std::string& description);
        static EntitySpecification* Create(const std::string& filename);

        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;

        using XmlContent::Load;
        using XmlContent::Save;

        const std::string& GetName() const;
        const std::string& GetDescription() const;

        const std::vector<std::reference_wrapper<ComponentConfig>> GetComponents();
        bool AddComponent(ComponentConfig* config);

    private:

        class Loader : ILoader {
        private:
            static Loader singleton_;
            Loader();
        public:
            Content* Load(const std::string& filename) override;
        };

    };

}
