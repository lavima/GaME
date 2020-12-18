#include <string>
#include <sstream>
#include <memory>
#include <list>
#include <vector>
#include <unordered_map>

#include "../global.h"
#include "format.h"
#include "command_line.h"
#include "../log.h"

namespace game::lib {

    CommandLine* CommandLine::singleton = nullptr;

    CommandLine::CommandLine() {}
    CommandLine::~CommandLine() {}

    CommandLine::CommandResult::CommandResult() {}
    CommandLine::CommandResult::~CommandResult() {}

    void CommandLine::SpecifyOption(OptionType type, const std::string& name, const std::string& description) {
				LOG_DEBUG("CommandLine::SpecifyOption %0", name);
        CommandLine::get().specifiedOptions.push_back(CommandOption{ type, name, description });
    }

    void CommandLine::SpecifyArgument(const std::string& name, const std::string& description, int minInstances, int maxInstances) {
				LOG_DEBUG("CommandLine::SpecifyArgument %0", name);
        CommandLine::get().specifiedArguments.push_back(CommandArgument{ name, description, minInstances, maxInstances });
    }

    bool CommandLine::Parse(const std::vector<std::string>& argumentValues) {

        // Insert the option declarations into a map for quick implementation_name_ lookup
        std::unordered_map<std::string, CommandOption*> optionMap;
        for (CommandOption option : CommandLine::get().specifiedOptions)
            optionMap[option.name] = &option;

        CommandLine::get().result = std::unique_ptr<CommandResult>(new CommandResult());
        CommandResult& result = *CommandLine::get().result;

        auto argvIter = argumentValues.begin();

        result.program = *argvIter;

        ++argvIter;
        while (argvIter!=argumentValues.end()&&CommandLine::IsOptionName(*argvIter)) {

            std::string optionName = (*argvIter).substr(2);

            if (!optionMap.count(optionName)) {
								LOG_DEBUG("CommandLine::Parse could not find option %0", optionName);
                result.num_errors++;
                ++argvIter;
                continue;
            }

            CommandOption& option = *optionMap[optionName];
            if (option.type==COMMANDOPTION_VALUE) {

                ++argvIter;
                if (argvIter==argumentValues.end()||CommandLine::IsOptionName(*argvIter)) {
										LOG_DEBUG("CommandLine::Parse could not find value for %0", optionName);
                    result.num_errors++;
								}

                result.options[optionName] = *argvIter;

            }
            else // COMMANDOPTION_LITERAL
                result.options[optionName] = "";

            ++argvIter;

        }

        for (auto argument:CommandLine::get().specifiedArguments) {

            int num = 0;
            for (; num<argument.max_instances&&argvIter!=argumentValues.end(); ++num) {
                result.arguments[argument.name].push_back(*argvIter);
                ++argvIter;
            }

            if (num<argument.min_instances)
                result.num_errors++;

        }

        if (argvIter!=argumentValues.end())
            result.num_errors++;

        return result.num_errors==0;
    }

    const std::string CommandLine::GetUsageString() {

        std::stringstream usage;
        usage<<"GaME ";

        usage<<(CommandLine::get().specifiedOptions.size()>0 ? "[OPTION]" : "");
        usage<<(CommandLine::get().specifiedOptions.size()>1 ? "..." : "");

        usage<<" ";

        for (CommandArgument argument : CommandLine::get().specifiedArguments) {

            int instances = 0;
            while (instances<argument.min_instances)
                usage<<argument.name+" ";

            if (argument.max_instances>argument.min_instances) {
                usage<<"[";
                while (instances<argument.min_instances-1)
                    usage<<argument.name+" ";
                usage<<argument.name+"]";
            }

            usage<<" ";
        }

        return usage.str();

    }

    const std::string& CommandLine::GetProgram() { return (*CommandLine::get().result).program; }

    bool CommandLine::HasOption(const std::string& name) { return (*CommandLine::get().result).options.count(name)>0; }
    const std::string& CommandLine::GetOption(const std::string& name) { return (*CommandLine::get().result).options[name]; }

    const std::vector<std::reference_wrapper<const std::string>> CommandLine::GetArgument(const std::string& name) {

        std::vector<std::string>& argumentValues = (*CommandLine::get().result).arguments[name];
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
