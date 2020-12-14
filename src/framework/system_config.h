/*
File: SystemConfig.h
Author: Lars Vidar Magnusson
 */

#pragma once

namespace game::addin {
	class ISystemProvider;
}

namespace game::framework {

#define XMLNAME_SYSTEMCONFIG "System"
#define XMLNAME_SYSTEMCONFIG_NAME "name"
#define XMLNAME_SYSTEMCONFIG_TYPENAME "typeName"

	class GAME_API SystemConfig : content::xml::IXmlSerializable {
		friend class addin::ISystemProvider;
	protected:

		class ILoader {
		public:
			virtual SystemConfig* Load(content::xml::XmlNode root_node) = 0;
		};

	private:

		static std::unordered_map<std::string, ILoader*>* loaders_;

		std::string name_;
		std::string type_name_;

		GameLoopStage update_stage_;

		float time_between_updates_;

	protected:

		SystemConfig() {}
		SystemConfig(const std::string& name, const std::string& type_name,
			GameLoopStage update_stage = GameLoopStage::PostGameUpdate,
			float time_between_updates = 1.0f/60.0f);
		SystemConfig(content::xml::XmlNode root_node);

	public:

    virtual ~SystemConfig();

		static SystemConfig* Create(content::xml::XmlNode root_node);
		static void RegisterType(const std::string& typeName, ILoader* loader);

		const std::string& GetName() const;
		const std::string& GetTypeName() const;

		bool Load(content::xml::XmlNode root_node) override;
		bool Save(content::xml::XmlNode root_node) override;

	};

}
