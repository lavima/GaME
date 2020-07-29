#pragma once

namespace game::graphics {

#define EXTENSION_IMAGE_JPG "jpg"
#define EXTENSION_IMAGE_PNG "png"
#define EXTENSION_IMAGE_TGA "tga"
#define EXTENSION_IMAGE_BMP "bmp"
#define EXTENSION_IMAGE_PSD "psd"
#define EXTENSION_IMAGE_GIF "gif"
#define EXTENSION_IMAGE_HDR "hdr"
#define EXTENSION_IMAGE_PIC "pic"
#define EXTENSION_IMAGE_PPM "ppm"
#define EXTENSION_IMAGE_PGM "pgm"

    class GAME_API Image : public data::Data {
    private:

        vector<uint8_t> image_data_;

        uint32_t width_;
        uint32_t height_;
        uint32_t num_channels_;

        Image(const string& filename) : data::Data(filename) {}

    public:

        bool Load() override;
        void Unload() override;

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
        uint32_t GetNumChannels() const;
        const vector<uint8_t>& GetData() const;

    private:

        class Loader : public ILoader {
        private:

            static Loader singleton;

            Loader();

        public:

            Data* Load(const string& filename);

        };

    };

}