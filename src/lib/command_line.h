/*
File: CommandLine.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::lib {

    enum OptionType {
        COMMANDOPTION_VALUE,
        COMMANDOPTION_LITERAL
    };

    /*
    * Structure for specifying command line options
    */
    struct GAME_API CommandOption {

        const OptionType Type;
        const std::string Name;
        const std::string Description;

    };

    /*
    * Structure for specifying command line arguments
    */
    struct GAME_API CommandArgument {

        const std::string Name;
        const std::string Description;
        const int MinInstances;
        const int MaxInstances;

    };

    /*
    * CommandLine contains functionality for parsing a command line. This provides functionality similar to parse_args
    * in GNU.
    * The format of the command line is PROGRAM [OPTIONS]... [ARGS]..., meaning that command line options must come before
    * the command line arguments.
    */
    class GAME_API CommandLine final {

    private:

        struct CommandResult {

            int NumErrors = 0;

            std::string Program;
            std::unordered_map<std::string, std::string> Options;
            std::unordered_map<std::string, std::vector<std::string>> Arguments;
        
            CommandResult();
            ~CommandResult();

        };

        static CommandLine* singleton;

        std::vector<CommandOption> specifiedOptions;
        std::vector<CommandArgument> specifiedArguments;

        std::unique_ptr<CommandResult> result;

        CommandLine();

        static CommandLine& get();

    public:

        ~CommandLine();

        static void SpecifyOption(OptionType type, const std::string& name, const std::string& description);
        static void SpecifyArgument(const std::string& name, const std::string& description, int minInstances, int maxInstances);

        static bool Parse(const std::vector<std::string>& argumentValues);

        static const std::string GetUsageString();

        static const std::string& GetProgram();

        static bool HasOption(const std::string& name);
        static const std::string& GetOption(const std::string& name);
        static const std::vector<std::reference_wrapper<const std::string>> GetArgument(const std::string& name);

    private:

        static bool IsOptionName(const std::string& arg);

    };

}
