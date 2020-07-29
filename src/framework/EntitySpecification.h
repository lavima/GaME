#pragma once

namespace game::framework {

#define EXTENSION_ENTITY "entity"

#define XMLNAME_ENTITY "Entity"
#define XMLNAME_ENTITY_NAME "Name"
#define XMLNAME_ENTITY_DESCRIPTION "Description"
#define XMLNAME_ENTITY_COMPONENT "Component"

    class EntitySpecification : public data::XmlData {
        friend class Entity;
    private:

        string name_;
        string description_;

        vector<unique_ptr<ComponentConfig>> components_;
        
        EntitySpecification(const string& name, const string& description);
        EntitySpecification(const string& filename);

    public:
        
        static EntitySpecification* Create(const string& name, const string& description);
        static EntitySpecification* Create(const string& filename);

        bool Load(data::xml::XmlNode root_node) override;
        bool Save(data::xml::XmlNode root_node) override;

        using XmlData::Load;
        using XmlData::Save;

        const string& GetName() const;
        const string& GetDescription() const;

    private:

        class Loader : ILoader {
        private:
            static Loader singleton_;
            Loader();
        public:
            Data* Load(const string& filename);
        };

    };

}