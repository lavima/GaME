#pragma once

namespace game::graphics {

#define EXTENSION_IMAGE_JPG ".jpg"
#define EXTENSION_IMAGE_PNG ".png"
#define EXTENSION_IMAGE_TGA ".tga"
#define EXTENSION_IMAGE_BMP ".bmp"
#define EXTENSION_IMAGE_PSD ".psd"
#define EXTENSION_IMAGE_GIF ".gif"
#define EXTENSION_IMAGE_HDR ".hdr"
#define EXTENSION_IMAGE_PIC ".pic"
#define EXTENSION_IMAGE_PPM ".ppm"
#define EXTENSION_IMAGE_PGM ".pgm"

    class GAME_API Image : public content::Content {
    private:

        std::vector<uint8_t> image_data_;

        uint32_t width_;
        uint32_t height_;
        uint32_t num_channels_;

        Image(const std::string& filename);

    public:

        virtual ~Image();

        bool Load() override;
        void Unload() override;

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
        uint32_t GetNumChannels() const;
        const std::vector<uint8_t>& GetData() const;

    private:

        class Loader : public ILoader {
        private:

            static Loader singleton;

            Loader();

        public:

            content::Content* Load(const std::string& filename) override;

        };

    };

}
