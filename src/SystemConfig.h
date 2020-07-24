/*
File: SystemConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace game {

#define XMLNAME_ENGINECOMPONENTCONFIG "EngineComponent"
#define XMLNAME_ENGINECOMPONENTCONFIG_NAME "name"
#define XMLNAME_ENGINECOMPONENTCONFIG_TYPENAME "typeName"


	class GAME_API SystemConfig : data::xml::IXmlSerializable {
	protected:

		class Loader {
		public:
			virtual SystemConfig* Load(data::xml::XmlNode root_node) = 0;
		};

	private:

		static unordered_map<string, Loader*> config_loaders_;

		string name_;
		string type_name_;

	protected:

		SystemConfig() {}
		SystemConfig(const string& name, const string& type_name);
		SystemConfig(data::xml::XmlNode root_node);

	public:

		static SystemConfig* Create(data::xml::XmlNode root_node);
		static void RegisterProvider(const string& typeName, Loader* loader);

		const string& GetName() const;
		const string& GetTypeName() const;

		bool Load(data::xml::XmlNode root_node) override;
		bool Save(data::xml::XmlNode root_node) override;

	};

}