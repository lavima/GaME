/*
File: Content.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::content {

    class GAME_API Content {
    protected:

        class ILoader {
        public:
            virtual Content* Load(const std::string& filename) = 0;
        };

    private:

        static std::unordered_map<std::string, ILoader*>* data_loaders_;

        std::string filename_;

    protected:

        Content(const std::string& filename);

    public:

        template<typename T> static T* Load(const std::string& filename);

        virtual bool Load() = 0;
        bool LoadFrom(const std::string& filename);
        
        virtual void Unload() = 0;

        const std::string& GetFilename();

    protected:

        static void RegisterType(const std::string& extension, ILoader* loader);
        static void RegisterTypes(const std::vector<std::string>& extensions, ILoader* loader);

    };

    template<typename T> T* Content::Load(const std::string& filename) {

        if (!std::is_base_of<Content, T>::value)
            return nullptr;

        const std::string extension = lib::FilePath::extension(filename);
        if (data_loaders_->count(extension)==0)
            return nullptr;

        return dynamic_cast<T*>(data_loaders_->at(extension)->Load(filename));

    }

    class GAME_API WritableContent : public Content {
    protected:

        WritableContent(const std::string& filename) : Content(filename) {}

    public:

        virtual bool Save() = 0;

    };

}
