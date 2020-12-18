namespace game::lib {

    inline const std::string ShaderExtension_Vertex = ".vertex";
    inline const std::string ShaderExtension_Fragment = ".frag";
    inline const std::string ShaderExtension_Spirv = ".spv";

    class GAME_API SpirvTools {

    public:
        
        static const TBuiltInResource default_resources_;

        static bool LoadRaw(const std::string& filename, std::vector<uint32_t>& buffer);
        static bool LoadAndCompile(const std::string& filename, std::vector<uint32_t>& buffer);

    private:

        static std::string LoadSource(const std::string& filename);
        static EShLanguage FindStage(const std::string& filename);

    };

}
