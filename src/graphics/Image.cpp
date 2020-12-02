#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../global.h"
#include "../content/Content.h"
#include "image.h"

namespace game::graphics {

    bool Image::Load() {

        int width, height, channels;
        stbi_uc* pixels = stbi_load(GetFilename().c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if (!pixels)
            return false;

        size_t num_bytes = (size_t)width*height*4;
        image_data_.resize(num_bytes);
        memcpy(image_data_.data(), pixels, num_bytes);

        stbi_image_free(pixels);

        width_ = static_cast<uint32_t>(width);
        height_ = static_cast<uint32_t>(height);
        num_channels_ = static_cast<uint32_t>(channels);

        return true;

    }

    void Image::Unload() {
        std::vector<uint8_t>().swap(image_data_);
    }

    uint32_t Image::GetWidth() const {
        return width_;
    }

    uint32_t Image::GetHeight() const {
        return height_;
    }

    uint32_t Image::GetNumChannels() const {
        return num_channels_;
    }

    const std::vector<uint8_t>& Image::GetData() const {
        return image_data_;
    }

    Image::Loader Image::Loader::singleton;

    Image::Loader::Loader() {
        std::vector<std::string> extensions = {
            EXTENSION_IMAGE_BMP,
            EXTENSION_IMAGE_GIF,
            EXTENSION_IMAGE_HDR,
            EXTENSION_IMAGE_JPG,
            EXTENSION_IMAGE_PGM,
            EXTENSION_IMAGE_PIC,
            EXTENSION_IMAGE_PNG,
            EXTENSION_IMAGE_PPM,
            EXTENSION_IMAGE_PSD,
            EXTENSION_IMAGE_TGA
        };
        Content::RegisterTypes(extensions, &singleton);
    }

    content::Content* Image::Loader::Load(const std::string& filename) {

        Image* image = new Image(filename);

        if (!image->Load())
            return nullptr;

        return image;

    }

}
