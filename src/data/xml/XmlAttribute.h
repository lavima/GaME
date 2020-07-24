#pragma once

namespace game::data::xml {

    class GAME_API XmlAttribute {
    private:

        pugi::xml_attribute internal_;

    public:

        class Iterator {
        private:

            pugi::xml_attribute attribute_;

            Iterator(pugi::xml_attribute attribute);

        public:

            Iterator operator++();
            bool operator!=(const Iterator& other) const;
            const XmlAttribute operator*() const;

            friend class XmlNode;
            friend class XmlAttribute;

        };

        XmlAttribute();
        XmlAttribute(pugi::xml_attribute attribute);

        const string GetName();
        void SetName(const string& name);

        const string GetValue();
        void SetValue(const string& value);

        bool operator!();

    };

}