#pragma once

namespace game::graphics::vulkan {

    class GAME_API Shader {
    private:

        VkDevice device_;

        VkShaderModule vertex_module_;
        VkShaderModule fragment_module_;

        VkPipelineShaderStageCreateInfo vertex_shader_stage_info_;
        VkPipelineShaderStageCreateInfo fragment_shader_stage_info_;

        Shader(VkDevice device, VkShaderModule vertex_module, VkShaderModule fragment_module);

        static VkShaderModule CreateModule(VkDevice device, const string& filename);

    public:

        static Shader* Create(VkDevice device, const string& vertex_filename, const string& frag_filename);

        vector<VkPipelineShaderStageCreateInfo> GetShaderStages() const;
        void Destroy();

    };
}
