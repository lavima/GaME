#pragma once

namespace game::framework {

#define XMLNAME_COMPONENTCONFIG "Component"
#define XMLNAME_COMPONENTCONFIG_NAME "name"
#define XMLNAME_COMPONENTCONFIG_TYPENAME "typeName"

    class ComponentConfig : public data::xml::IXmlSerializable {
    protected:

        class ICreator {
        public:
            virtual ComponentConfig* Create(const string& name, const string& type_name) = 0;
            virtual ComponentConfig* Create(data::xml::XmlNode root_node) = 0;
        };

    private:

        static unordered_map<string, ICreator*>* creators_;

        string name_;
        string type_name_;

        bool shared_;

    protected:

        ComponentConfig(const string& name, const string& type_name, bool shared);
        ComponentConfig(data::xml::XmlNode root_node);

    public:

        static ComponentConfig* Create(const string& name, const string& type_name, bool shared = false);
        static ComponentConfig* Create(data::xml::XmlNode root_node);
        
        static void RegisterType(const string& type_name, ICreator* creator);

        bool Load(data::xml::XmlNode root_node) override;
        bool Save(data::xml::XmlNode root_node) override;

        const string& GetName() const;
        const string& GetTypeName() const;
        const bool IsShared() const;

    };

}