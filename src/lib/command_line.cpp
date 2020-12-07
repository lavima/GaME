#include <string>
#include <sstream>
#include <memory>
#include <unordered_map>

#include "../global.h"
#include "command_line.h"

namespace game::lib {

    CommandLine* CommandLine::singleton = nullptr;

    void CommandLine::SpecifyOption(OptionType type, const std::string& name, const std::string& description) {
        CommandLine::get().specifiedOptions.push_back(CommandOption{ type, name, description });
    }

    void CommandLine::SpecifyArgument(const std::string& name, const std::string& description, int minInstances, int maxInstances) {
        CommandLine::get().specifiedArguments.push_back(CommandArgument{ name, description, minInstances, maxInstances });
    }

    bool CommandLine::Parse(const std::vector<std::string>& argumentValues) {

        // Insert the option declarations into a map for quick implementation_name_ lookup
        std::unordered_map<std::string, CommandOption*> optionMap;
        for (CommandOption option : CommandLine::get().specifiedOptions)
            optionMap[option.Name] = &option;

        CommandLine::get().result = std::unique_ptr<commandResult>(new commandResult());
        commandResult& result = *CommandLine::get().result;

        auto argvIter = argumentValues.begin();

        if (CommandLine::IsOptionName(*argvIter)) {
            result.NumErrors++;
        }
        result.Program = *argvIter;

        ++argvIter;
        while (argvIter!=argumentValues.end()&&CommandLine::IsOptionName(*argvIter)) {

            std::string optionName = (*argvIter).substr(2);

            if (!optionMap.count(optionName)) {
                result.NumErrors++;
                ++argvIter;
                continue;
            }

            CommandOption& option = *optionMap[optionName];
            if (option.Type==COMMANDOPTION_VALUE) {

                ++argvIter;
                if (argvIter==argumentValues.end()||CommandLine::IsOptionName(*argvIter))
                    result.NumErrors++;

                result.Options[optionName] = *argvIter;

            }
            else // COMMANDOPTION_LITERAL
                result.Options[optionName] = "";

            ++argvIter;

        }

        for (auto argument:CommandLine::get().specifiedArguments) {

            int num = 0;
            for (; num<argument.MaxInstances&&argvIter!=argumentValues.end(); ++num) {
                result.Arguments[argument.Name].push_back(*argvIter);
                ++argvIter;
            }

            if (num<argument.MinInstances)
                result.NumErrors++;

        }

        if (argvIter!=argumentValues.end())
            result.NumErrors++;

        return result.NumErrors==0;
    }

    const std::string CommandLine::GetUsageString() {

        std::stringstream usage;
        usage<<"GaME ";

        usage<<(CommandLine::get().specifiedOptions.size()>0 ? "[OPTION]" : "");
        usage<<(CommandLine::get().specifiedOptions.size()>1 ? "..." : "");

        usage<<" ";

        for (CommandArgument argument : CommandLine::get().specifiedArguments) {

            int instances = 0;
            while (instances<argument.MinInstances)
                usage<<argument.Name+" ";

            if (argument.MaxInstances>argument.MinInstances) {
                usage<<"[";
                while (instances<argument.MinInstances-1)
                    usage<<argument.Name+" ";
                usage<<argument.Name+"]";
            }

            usage<<" ";
        }

        return usage.str();

    }

    const std::string& CommandLine::GetProgram() { return (*CommandLine::get().result).Program; }

    bool CommandLine::HasOption(const std::string& name) { return (*CommandLine::get().result).Options.count(name)>0; }
    const std::string& CommandLine::GetOption(const std::string& name) { return (*CommandLine::get().result).Options[name]; }

    const std::vector<std::reference_wrapper<const std::string>> CommandLine::GetArgument(const std::string& name) {

        std::vector<std::string>& argumentValues = (*CommandLine::get().result).Arguments[name];
        return std::vector<std::reference_wrapper<const std::string>>(argumentValues.begin(), argumentValues.end());

    }

    CommandLine& CommandLine::get() {

        if (!singleton)
            singleton = new CommandLine();
        return *singleton;

    }

    bool CommandLine::IsOptionName(const std::string& arg) {

        if (arg.find("--")!=0)
            return false;
        return true;

    }

}
