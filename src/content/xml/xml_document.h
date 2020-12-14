#pragma once

namespace game::content::xml {

    class GAME_API XmlDocument {

    private:

        std::unique_ptr<pugi::xml_document> internal_;

    public:

        XmlDocument();
        ~XmlDocument();
        XmlDocument(XmlDocument& other);

        bool Load(const std::string& filename);
        bool Save(const std::string& filename);

        void Unload();

        XmlNode GetDocumentElement();

    };

}
