#include <string>
#include <vector>
#include <ios>
#include <iostream>
#include <fstream>

#include <vulkan/vulkan.h>

#include "../../global.h"
#include "Shader.h"

namespace game::graphics::vulkan {

    Shader::Shader(VkDevice device, VkShaderModule vertex_module, VkShaderModule fragment_module) {

        device_ = device;
        vertex_module_ = vertex_module;
        fragment_module_ = fragment_module;

        vertex_shader_stage_info_.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertex_shader_stage_info_.pNext = nullptr;
        vertex_shader_stage_info_.flags = 0;
        vertex_shader_stage_info_.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertex_shader_stage_info_.module = vertex_module_;
        vertex_shader_stage_info_.pName = "main";
        vertex_shader_stage_info_.pSpecializationInfo = nullptr;

        fragment_shader_stage_info_.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragment_shader_stage_info_.pNext = nullptr;
        fragment_shader_stage_info_.flags = 0;
        fragment_shader_stage_info_.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragment_shader_stage_info_.module = fragment_module_;
        fragment_shader_stage_info_.pName = "main";
        fragment_shader_stage_info_.pSpecializationInfo = nullptr;

    }

    bool _ReadFile(const std::string& filename, std::vector<char> *buffer) {

        std::ifstream file(filename, std::ios::ate|std::ios::binary);

        if (!file.is_open())
            return false;

        size_t file_size = (size_t)file.tellg();
        buffer->resize(file_size);

        file.seekg(0);
        file.read(buffer->data(), file_size);

        file.close();

        return true;

    }

    VkShaderModule Shader::CreateModule(VkDevice device, const std::string& filename) {

        std::vector<char> code;
        if (!_ReadFile(filename, &code))
            return VK_NULL_HANDLE;

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shader_module;
        if (vkCreateShaderModule(device, &createInfo, nullptr, &shader_module)!=VK_SUCCESS)
            return VK_NULL_HANDLE;

        return shader_module;

    }

    Shader* Shader::Create(VkDevice device, const std::string& vertex_filename, const std::string& frag_filename) {

        VkShaderModule vertex_module = CreateModule(device, vertex_filename);
        if (vertex_module==VK_NULL_HANDLE)
            return nullptr;

        VkShaderModule fragment_module = CreateModule(device, frag_filename);
        if (fragment_module==VK_NULL_HANDLE)
            return nullptr;

        Shader* shader = new Shader(device, vertex_module, fragment_module);
        
        return shader;

    }

    std::vector<VkPipelineShaderStageCreateInfo> Shader::GetShaderStages() const {
        return std::vector<VkPipelineShaderStageCreateInfo>{ vertex_shader_stage_info_, fragment_shader_stage_info_ };
    }

    void Shader::Destroy() {
        
        vkDestroyShaderModule(device_, vertex_module_, nullptr);
        vkDestroyShaderModule(device_, fragment_module_, nullptr);

    }

}
