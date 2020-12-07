#pragma once

namespace game::content::xml {

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

        const std::string GetName();
        void SetName(const std::string& name);

        const std::string GetValue();
        void SetValue(const std::string& value);

        bool operator!();

    };

}
