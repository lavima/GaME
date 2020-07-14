/*
File: PlatformConfig.h
Author: Lars Vidar Magnusson
*/

#pragma once

#define PLATFORM_CONFIG_EXTENSION "platform_config"

#define XMLNAME_PLATFORMCONFIG "PlatformConfig"
#define XMLNAME_PLATFORMCONFIG_WIDTH "Width"
#define XMLNAME_PLATFORMCONFIG_HEIGHT "Height"
#define XMLNAME_PLATFORMCONFIG_FULLSCREEN "Fullscreen"

#define DEFAULT_GRAPHICALPLATFORM_WIDTH 800
#define DEFAULT_GRAPHICALPLATFORM_HEIGHT 600
#define DEFAULT_GRAPHICALPLATFORM_FULLSCREEN false

/*
* PlatformConfig is the base class for all platform configuration types. The class 
* features a factory pattern for loading all registered configuration types.
*   
*/
class PlatformConfig : public XmlSerializable {
protected:

    class Loader {
    public:
        virtual PlatformConfig* Load(const string& implementation_name, XmlNode root_node) = 0;
    };

private:

    static unordered_map<string, Loader*>* configuration_loaders_;
    
    string implementation_name_;


protected:

    PlatformConfig(const string& implementation_name);

    static void RegisterImplementation(const string& implementation_name, Loader* loader);
    
public:

    static PlatformConfig* Create(XmlNode root_node);


    const string &GetImplementationName();
    void SetImplementationName(const string &name);

};



class GraphicalPlatformConfig : public PlatformConfig {
private:

    uint32_t width_;
    uint32_t height_;
    bool fullscreen_;

public:

    GraphicalPlatformConfig(const string& implementation_name);
    GraphicalPlatformConfig(const string &implementation_name, int width, int height, bool fullscreen);

    bool Load(XmlNode root_node) override; 
    bool Save(XmlNode root_node) override;

    uint32_t GetWidth() const;
    void SetWidth(uint32_t width);

    uint32_t GetHeight() const;
    void SetHeight(uint32_t height);
    
    bool GetFullscreen() const;
    void SetFullscreen(bool fullscreen);

};
