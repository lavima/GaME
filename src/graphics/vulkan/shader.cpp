#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>

#include <vulkan/vulkan.h>

#include "glslang/Public/ShaderLang.h"
#include "SPIRV/GlslangToSpv.h"

#include "../../global.h"
#include "../../lib/format.h"
#include "../../lib/file_path.h"
#include "../../lib/spirv_tools.h"
#include "../../log.h"
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

    VkShaderModule Shader::CreateModule(VkDevice device, const std::string& filename) {

        LOG_TRACE("Shader::CreateModule %0", filename);
        std::vector<uint32_t> code;
        std::string extension = lib::FilePath::extension(filename);
        if (extension==lib::ShaderExtension_Spirv&&!lib::SpirvTools::LoadRaw(filename, code))
            return VK_NULL_HANDLE;
        else if (!lib::SpirvTools::LoadAndCompile(filename, code))
            return VK_NULL_HANDLE;

        LOG_TRACE("Shader::CreateModule Code Size %0", code.size());
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size()*4;
        createInfo.pCode = code.data();

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
