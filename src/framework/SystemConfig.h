/*
File: SystemConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace game {

#define XMLNAME_SYSTEMCONFIG "System"
#define XMLNAME_SYSTEMCONFIG_NAME "name"
#define XMLNAME_SYSTEMCONFIG_TYPENAME "typeName"

	//class addin::ISystemProvider;

	class GAME_API SystemConfig : data::xml::IXmlSerializable {
		friend class addin::ISystemProvider;
	protected:

		class ILoader {
		public:
			virtual SystemConfig* Load(data::xml::XmlNode root_node) = 0;
		};

	private:

		static unordered_map<string, ILoader*>* loaders_;

		string name_;
		string type_name_;

	protected:

		SystemConfig() {}
		SystemConfig(const string& name, const string& type_name);
		SystemConfig(data::xml::XmlNode root_node);

	public:

		static SystemConfig* Create(data::xml::XmlNode root_node);
		static void RegisterType(const string& typeName, ILoader* loader);

		const string& GetName() const;
		const string& GetTypeName() const;

		bool Load(data::xml::XmlNode root_node) override;
		bool Save(data::xml::XmlNode root_node) override;

	};

}