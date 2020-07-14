#include "../GaME.h"

CommandLine *CommandLine::singleton = nullptr;

void CommandLine::SpecifyOption(OptionType type, const string &name, const string &description) {
    CommandLine::get().specifiedOptions.push_back(CommandOption{ type, name, description });
}

void CommandLine::SpecifyArgument(const string &name, const string &description, int minInstances, int maxInstances) {
    CommandLine::get().specifiedArguments.push_back(CommandArgument{ name, description, minInstances, maxInstances });
}

bool CommandLine::Parse(const vector<string> &argumentValues) {
    
    // Insert the option declarations into a map for quick implementation_name_ lookup
    unordered_map<string, CommandOption *> optionMap;
    for (CommandOption option : CommandLine::get().specifiedOptions)
        optionMap[option.Name] = &option;

    CommandLine::get().result = unique_ptr<commandResult>(new commandResult());
    commandResult &result = *CommandLine::get().result;
    
    auto argvIter = argumentValues.begin();

    if (CommandLine::IsOptionName(*argvIter)) {
        result.NumErrors++;
    }
    result.Program = *argvIter;

    ++argvIter;
    while (argvIter != argumentValues.end() && CommandLine::IsOptionName(*argvIter)) {
        
        string optionName = (*argvIter).substr(2);
        
        if (!optionMap.count(optionName)) {
            result.NumErrors++;
            ++argvIter;
            continue;
        }

        CommandOption &option = *optionMap[optionName];
        if (option.Type == COMMANDOPTION_VALUE) {

            ++argvIter;
            if (argvIter == argumentValues.end() || CommandLine::IsOptionName(*argvIter)) 
                result.NumErrors++;
            
            result.Options[optionName] = *argvIter;

        }
        else // COMMANDOPTION_LITERAL
            result.Options[optionName] = "";

        ++argvIter; 

    }    

    for (auto argument : CommandLine::get().specifiedArguments) {
        
        int num = 0;
        for (; num < argument.MaxInstances && argvIter != argumentValues.end(); ++num) {
            result.Arguments[argument.Name].push_back(*argvIter);
            ++argvIter;
        }

        if (num < argument.MinInstances)
            result.NumErrors++;

    }

    if (argvIter != argumentValues.end())
        result.NumErrors++;

    return result.NumErrors == 0;
}

const string CommandLine::GetUsageString() {

    stringstream usage;
    usage << "GaME "; 

    usage << (CommandLine::get().specifiedOptions.size()>0 ? "[OPTION]" : "");
    usage << (CommandLine::get().specifiedOptions.size()>1 ? "..." : "");

    usage << " ";

    for (CommandArgument argument : CommandLine::get().specifiedArguments) {

        int instances = 0;
        while (instances < argument.MinInstances)
            usage << argument.Name + " ";

        if (argument.MaxInstances > argument.MinInstances) {
            usage << "[";
            while (instances < argument.MinInstances - 1)
                usage << argument.Name + " ";
            usage << argument.Name + "]";
        }

        usage << " ";
    }

    return usage.str();

}

const string &CommandLine::GetProgram() { return (*CommandLine::get().result).Program; }

bool CommandLine::HasOption(const string &name) { return (*CommandLine::get().result).Options.count(name) > 0; }
const string &CommandLine::GetOption(const string &name) { return (*CommandLine::get().result).Options[name]; }

const vector<reference_wrapper<const string>> CommandLine::GetArgument(const string &name) {

    vector<string> &argumentValues = (*CommandLine::get().result).Arguments[name];
    return vector<reference_wrapper<const string>>(argumentValues.begin(), argumentValues.end());

}

CommandLine &CommandLine::get() { 

    if (!singleton)
        singleton = new CommandLine();
    return *singleton; 

}

bool CommandLine::IsOptionName(const string &arg) {

    if (arg.find("--") != 0)
        return false;
    return true;

}
