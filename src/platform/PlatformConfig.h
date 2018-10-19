/*
File: PlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace std;

class PlatformConfig {

protected:

    string typeName;

    PlatformConfig();
    PlatformConfig(const string &typeName);

public:

    static PlatformConfig * Load(xercesc::DOMDocument *document);

    const string &GetTypeName();
    void SetTypeName(const string &typeName);

};

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_FULLSCREEN false

class GraphicalPlatformConfig : public PlatformConfig {

protected:

    int width;
    int height;
    bool fullscreen;

    GraphicalPlatformConfig();
    GraphicalPlatformConfig(const string &typeName, int width, int height, bool fullscreen);

public:

    static GraphicalPlatformConfig *Load(xercesc::DOMElement *element);

    int GetWidth();
    void SetWidth(int width);

    int GetHeight();
    void SetHeight(int height);
    
    bool GetFullscreen();
    void SetFullscreen(bool fullscreen);

};