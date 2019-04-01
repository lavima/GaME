/*
File: PlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define PLATFORM_CONFIG_EXTENSION "platform_config"

class PlatformConfig : XMLData<PlatformConfig> {
private:
    
    string typeName;


protected:

    PlatformConfig(const string &typeName);

public:

    /*
    * Factory function for loading any type of platform configuration from an XML-document
    */
    static PlatformConfig *Load(pugi::xml_document &xmlDocument);

    const string &GetTypeName();
    void SetTypeName(const string &typeName);

private:

    class __Factory : DataFactory<GraphicalPlatformConfig> {
    private:

        static __Factory singleton;

        __Factory();

    public:

        PlatformConfig *Load(const string &filename);

    };

};

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FULLSCREEN false

class GraphicalPlatformConfig : public PlatformConfig {

  friend class PlatformConfig;

private:

    int width;
    int height;
    bool fullscreen;

protected:

    GraphicalPlatformConfig(const string &name);
    GraphicalPlatformConfig(const string &name, int width, int height, bool fullscreen);
    GraphicalPlatformConfig(pugi::xml_node &xmlNode);

public:

    int GetWidth();
    void SetWidth(int width);

    int GetHeight();
    void SetHeight(int height);
    
    bool GetFullscreen();
    void SetFullscreen(bool fullscreen);

};
