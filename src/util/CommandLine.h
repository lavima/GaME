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

struct CommandArgument {

    const string Name;
    const string Description;
    const int MinInstances;
    const int MaxInstances;

};

typedef unordered_map<string, string> NameValueMap;
typedef pair<string, string> NameValuePair;
typedef NameValueMap::iterator NameValueMapIter;
typedef unordered_map<string, vector<string>> NameValuesMap;
typedef pair<string, vector<string>> NameValuesPair;
typedef NameValueMap::iterator NameValuesMapIter;

typedef vector<CommandOption> OptionVector;
typedef OptionVector::iterator OptionVectorIter;
typedef vector<CommandArgument> ArgumentVector;
typedef ArgumentVector::iterator ArgumentVectorIter;
typedef ArgumentVector::reverse_iterator ArgumentVectorRIter;

enum CommandLineToken {
    COMMANDLINE_NONE,
    COMMANDLINE_NAME,
    COMMANDLINE_VALUE,
    COMMANDLINE_ASSIGN
};

/*
* Command line parse results
*/
struct CommandLineResult {

    int NumErrors = 0;

    string ExecutablePath;
    NameValueMap Options;
    NameValuesMap Arguments;

};

class CommandLineTokenizer {
private:

    const string *linePtr;
    size_t pos;
    size_t follow;
    string tokenString;

public:

    CommandLineTokenizer(const string &commandLine);

    CommandLineToken GetNext();
    const string &GetTokenString();
};

/*
* CommandLine contains static functionality for parsing a command line
*/
class CommandLine {

public:

    static CommandLineResult *Parse(ArgumentVector &arguments, OptionVector &options, const string &commandLine);

    static const string GetExecutablePath(const string &commandLine);

    static const string GetDescriptionString(ArgumentVector &arguments, OptionVector &options);

};