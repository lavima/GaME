/*
File: CommandLine.h
Author: Lars Vidar Magnusson
*/

#pragma once

using namespace std;

enum OptionType {
    COMMANDOPTION_VALUE,
    COMMANDOPTION_LITERAL
};

/*
* Structure for specifying command line options
*/
struct CommandOption {

    const OptionType Type;
    const string Name;
    const string Description;

};

/*
* Structure for specifying command line arguments
*/
struct CommandArgument {

    const string Name;
    const string Description;
    const int MinInstances;
    const int MaxInstances;

};

/*
* CommandLine contains functionality for parsing a command line. This provides functionality similar to parse_args
* in GNU. 
* The format of the command line is PROGRAM [OPTIONS]... [ARGS]..., meaning that command line options must come before
* the command line arguments.
*/
class CommandLine {

private:
   
    struct commandResult {

        int NumErrors = 0;

        string Program;
        unordered_map<string, string> Options;
        unordered_map<string, vector<string>> Arguments;

    };

    static CommandLine *singleton;

    vector<CommandOption> specifiedOptions;
    vector<CommandArgument> specifiedArguments;

    unique_ptr<commandResult> result;

    CommandLine() {}

    static CommandLine &get();

public:

    static void SpecifyOption(OptionType type, const string &name, const string &description); 
    static void SpecifyArgument(const string &name, const string &description, int minInstances, int maxInstances); 

    static bool Parse(const vector<string> &argumentValues);

    static const string GetUsageString();

    static const string &GetProgram();

    static bool HasOption(const string &name);
    static const string &GetOption(const string &name);
    static const vector<reference_wrapper<const string>> GetArgument(const string &name);

private:

    static bool IsOptionName(const string &arg);

};
