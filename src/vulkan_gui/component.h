#pragma once

namespace game::vulkangui {

    class TextComponent : framework::Component {
        friend class SystemProvider;
    private:

        TextComponent(framework::Entity& entity, const string& name, const string& type_name);
        TextComponent(framework::Entity& entity, framework::ComponentConfig& config);

    public:

        bool Initialize() override;
        void Update(const framework::GameTime& gameTime) override;
        void Destroy() override;

    };
}