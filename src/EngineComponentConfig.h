/*
File: EngineComponentConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

#define XMLNAME_ENGINECOMPONENTCONFIG "EngineComponentConfig"
#define XMLNAME_ENGINECOMPONENTCONFIG_NAME "name"
#define XMLNAME_ENGINECOMPONENTCONFIG_TYPENAME "typeName"

class EngineComponentConfig;

typedef EngineComponentConfig *(*LoadEngineComponentConfigFun)(const string &, pugi::xml_node rootNode);
#define ADDINFUN_ENGINECOMPONENTCONFIG_LOAD "LoadEngineComponentConfig" 
typedef void (*SaveEngineComponentConfigFun)(const string &, EngineComponentConfig &config, pugi::xml_node rootNode);
#define ADDINFUN_ENGINECOMPONENTCONFIG_SAVE "SaveEngineComponentConfig" 

class EngineComponentConfig : XMLSerializable {
private:

	static unordered_map<string, LoadEngineComponentConfigFun> configLoaders;
	static unordered_map<string, SaveEngineComponentConfigFun> configSavers;

	string name;
	string typeName;

protected:

	EngineComponentConfig() {}
	EngineComponentConfig(const string &name, const string &typeName);

public:

	static EngineComponentConfig *Create(pugi::xml_node rootNode);
	static void RegisterProvider(const string &typeName, LoadEngineComponentConfigFun loadFun, SaveEngineComponentConfigFun saveFun);

	const string &GetName() const;
	const string &GetTypeName() const;

	bool Load(pugi::xml_node) override;
	bool Save(pugi::xml_node) override;

};
