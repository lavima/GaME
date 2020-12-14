#pragma once

namespace game::addin {
    class IComponentProvider;
}

namespace game::framework {

#define XMLNAME_COMPONENTCONFIG "Component"
#define XMLNAME_COMPONENTCONFIG_NAME "name"
#define XMLNAME_COMPONENTCONFIG_TYPENAME "typeName"

    class ComponentConfig : public content::xml::IXmlSerializable {
        friend class addin::IComponentProvider;
    protected:

        class ICreator {
        public:
            virtual ComponentConfig* Create(const std::string& name, const std::string& type_name) = 0;
            virtual ComponentConfig* Create(content::xml::XmlNode root_node) = 0;
        };

    private:

        static std::unordered_map<std::string, ICreator*>* creators_;

        std::string name_;
        std::string type_name_;

        GameLoopStage update_stage_;

        float time_between_updates_;

        bool shared_between_entities_;

    protected:

        ComponentConfig(const std::string& name, const std::string& type_name, bool shared = true);
        ComponentConfig(content::xml::XmlNode root_node);

    public:

        virtual ~ComponentConfig(); 

        static ComponentConfig* Create(const std::string& name, const std::string& type_name, bool shared = false);
        static ComponentConfig* Create(content::xml::XmlNode root_node);
        
        static void RegisterType(const std::string& type_name, ICreator* creator);

        bool Load(content::xml::XmlNode root_node) override;
        bool Save(content::xml::XmlNode root_node) override;

        const std::string& GetName() const;
        const std::string& GetTypeName() const;
        bool IsShared() const;

    };

}
