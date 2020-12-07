#pragma once

namespace game::content::xml {

    class GAME_API XmlNode {
    private:

        pugi::xml_node internal_;

    public:

        class Iterator {
        private:

            pugi::xml_node node_;

            Iterator(pugi::xml_node node);

        public:

            Iterator operator++();
            bool operator!=(const Iterator& other) const;
            const XmlNode operator*() const;

            friend class XmlNode;

        };

        class NamedIterator {
        private:

            pugi::xml_node node_;
            std::string name_;

        public:

            NamedIterator(pugi::xml_node node_ptr, const std::string& name);

            NamedIterator operator++();
            bool operator!=(const NamedIterator& other) const;
            const XmlNode operator*() const;

            friend class XmlNode;

        };

        XmlNode();
        XmlNode(pugi::xml_node node);

        const std::string GetName() const;
        void SetName(const std::string& name);

        const std::string GetValue() const;
        void SetValue(const std::string& value);

        XmlNode AddChild();
        XmlNode AddChild(const std::string& name);

        bool HasChild(const std::string& name);

        XmlNode GetChild(const std::string& name);

        XmlRange<Iterator> GetChildren();
        XmlRange<NamedIterator> GetChildren(const std::string& name);

        XmlAttribute AddAttribute(const std::string& name);

        XmlAttribute GetAttribute(const std::string& name);
        XmlRange<XmlAttribute::Iterator> GetAttributes();

        bool operator!() const;
        operator bool() const;

    };

}
