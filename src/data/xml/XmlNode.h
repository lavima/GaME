#pragma once

namespace game::data::xml {

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
            string name_;

        public:

            NamedIterator(pugi::xml_node node_ptr, const string& name);

            NamedIterator operator++();
            bool operator!=(const NamedIterator& other) const;
            const XmlNode operator*() const;

            friend class XmlNode;

        };

        XmlNode();
        XmlNode(pugi::xml_node node);

        const string GetName() const;
        void SetName(const string& name);

        const string GetValue() const;
        void SetValue(const string& value);

        XmlNode AddChild();
        XmlNode AddChild(const string& name);

        bool HasChild(const string& name);

        XmlNode GetChild(const string& name);

        XmlRange<Iterator> GetChildren();
        XmlRange<NamedIterator> GetChildren(const string& name);

        XmlAttribute AddAttribute(const string& name);

        XmlAttribute GetAttribute(const string& name);
        XmlRange<XmlAttribute::Iterator> GetAttributes();

        bool operator!() const;
        operator bool() const;

    };

}