/*
File: PlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

class PlatformConfig {

private:
    
    string *typeName;

    PlatformConfig() {}

protected:

    PlatformConfig(const string &typeName);

public:

    static PlatformConfig *Load(pugi::xml_document &xmlDocument);

    const string &GetTypeName();
    void SetTypeName(const string &typeName);

};

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FULLSCREEN false

class GraphicalPlatformConfig : public PlatformConfig {

private:

    int width;
    int height;
    bool fullscreen;

    GraphicalPlatformConfig();
    GraphicalPlatformConfig(const string &name);
    GraphicalPlatformConfig(const string &name, int width, int height, bool fullscreen);

public:

    static GraphicalPlatformConfig *Load(pugi::xml_node &xmlNode);

    int GetWidth();
    void SetWidth(int width);

    int GetHeight();
    void SetHeight(int height);
    
    bool GetFullscreen();
    void SetFullscreen(bool fullscreen);

};
