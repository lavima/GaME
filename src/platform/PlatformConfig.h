/*
File: PlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define PLATFORM_CONFIG_EXTENSION "platform_config"

class PlatformConfig : public XMLData {
private:
    
    string typeName;


protected:

    PlatformConfig(const string &filename);
    PlatformConfig(const string &filename, pugi::xml_document *document);
    PlatformConfig(const string &filename, const string &typeName);

public:

    const string &GetTypeName();
    void SetTypeName(const string &typeName);

private:

    class __Factory : public DataFactory {
    private:

        static __Factory singleton;

        __Factory();

    public:

        Data *Load(const string &filename);

    };

};

#define DEFAULT_GRAPHICALPLATFORM_WIDTH 800
#define DEFAULT_GRAPHICALPLATFORM_HEIGHT 600
#define DEFAULT_GRAPHICALPLATFORM_FULLSCREEN false

#define XMLNAME_GRAPHICALPLATFORMCONFIG "GraphicalPlatformConfig"
#define XMLNAME_GRAPHICALPLATFORMCONFIG_WIDTH "Width"
#define XMLNAME_GRAPHICALPLATFORMCONFIG_HEIGHT "Height"
#define XMLNAME_GRAPHICALPLATFORMCONFIG_FULLSCREEN "Fullscreen"

class GraphicalPlatformConfig : public PlatformConfig {
private:

    int width;
    int height;
    bool fullscreen;

public:

    GraphicalPlatformConfig(const string &filename);
    GraphicalPlatformConfig(const string &filename, pugi::xml_document *document);
    GraphicalPlatformConfig(const string &filename, const string &name);
    GraphicalPlatformConfig(const string &filename, const string &name, int width, int height, bool fullscreen);


    bool Load(pugi::xml_node rootNode); 
    bool Save(pugi::xml_node rootNode);

    int GetWidth();
    void SetWidth(int width);

    int GetHeight();
    void SetHeight(int height);
    
    bool GetFullscreen();
    void SetFullscreen(bool fullscreen);

};
