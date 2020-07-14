/*
File: EngineComponentConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

#define XMLNAME_ENGINECOMPONENTCONFIG "EngineComponent"
#define XMLNAME_ENGINECOMPONENTCONFIG_NAME "name"
#define XMLNAME_ENGINECOMPONENTCONFIG_TYPENAME "typeName"



class EngineComponentConfig : XmlSerializable {
private:

	static unordered_map<string, LoadEngineComponentConfigFun> config_loaders_;
	static unordered_map<string, SaveEngineComponentConfigFun> config_savers_;

	string name_;
	string type_name_;

protected:

	EngineComponentConfig() {}
	

public:

	EngineComponentConfig(const string& name, const string& type_name);
	EngineComponentConfig(XmlNode root_node);

	static EngineComponentConfig *Create(XmlNode root_node);
	static void RegisterProvider(const string &typeName, LoadEngineComponentConfigFun loadFun, SaveEngineComponentConfigFun saveFun);

	const string &GetName() const;
	const string &GetTypeName() const;

	bool Load(XmlNode root_node) override;
	bool Save(XmlNode root_node) override;

};
