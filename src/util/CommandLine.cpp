#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "CommandLine.h"

CommandLineTokenizer::CommandLineTokenizer(const string &commandLine) {
    
    linePtr = &commandLine;
    pos = follow = 0;

}

CommandLineToken CommandLineTokenizer::GetNext() {

    while (pos < linePtr->length() && ((*linePtr)[pos] == ' ' || (*linePtr)[pos] == '\t'))
        ++pos;

    if (pos >= linePtr->length())
        return COMMANDLINE_NONE;

    if ((*linePtr)[pos] == '-') {

        if (pos + 1 >= linePtr->length() || (*linePtr)[pos + 1] != '-')
            return COMMANDLINE_NONE;
        
        pos += 2;
        follow = min(min((*linePtr).find(' ', pos + 1), (*linePtr).find('\t', pos + 1)), (*linePtr).find('=', pos + 1));
        
        tokenString = linePtr->substr(pos, follow - pos);
        
        pos = follow;
        
        return COMMANDLINE_NAME;

    }
    else if ((*linePtr)[pos] == '=') {
        
        ++pos;
        
        return COMMANDLINE_ASSIGN;

    }
    else {
        
        if ((*linePtr)[pos]=='"') {
            ++pos;
            follow = (*linePtr).find('"', pos+1);
        }
        else {
            follow = pos+1;
            while (follow < linePtr->length() && ((*linePtr)[follow] != ' ' || (*linePtr)[follow] != '\t'))
                ++follow;
        }

        tokenString = linePtr->substr(pos, follow - pos);

        pos = follow + 1;

        return COMMANDLINE_VALUE;

    }

}

const string &CommandLineTokenizer::GetTokenString() { return tokenString; }

CommandLineResult *CommandLine::Parse(ArgumentVector &arguments, OptionVector &options, const string &commandLine) {
    
    // Insert the option declarations into a map for quick name lookup
    unordered_map<string, CommandOption *> optionMap;
    for (OptionVectorIter iter = options.begin(); iter != options.end(); ++iter)
        optionMap.insert(pair<string, CommandOption *>((*iter).Name, &(*iter)));

    CommandLineResult *result = new CommandLineResult();
    CommandLineTokenizer tokenizer(commandLine);
    
    CommandLineToken token = tokenizer.GetNext();
    
    if (token != COMMANDLINE_VALUE)
        result->NumErrors++;

    result->ExecutablePath = tokenizer.GetTokenString();

    token = tokenizer.GetNext();
    while (token == COMMANDLINE_NAME) {
        
        string optionName = tokenizer.GetTokenString();
        
        if (!optionMap.count(optionName)) {
            result->NumErrors++;
            token = tokenizer.GetNext();
            if (token == COMMANDLINE_ASSIGN && tokenizer.GetNext() != COMMANDLINE_VALUE) {
                result->NumErrors++;
                tokenizer.GetNext();
            }
            continue;
        }

        CommandOption &option = *optionMap[optionName];
        if (option.Type == COMMANDOPTION_VALUE) {

            if (tokenizer.GetNext() != COMMANDLINE_ASSIGN || tokenizer.GetNext() != COMMANDLINE_VALUE)
                result->NumErrors++;
            
            result->Options[optionName] = tokenizer.GetTokenString();

        }

        token = tokenizer.GetNext();
    }    

    vector<string> argumentValues;
    if (token == COMMANDLINE_VALUE)
        argumentValues.push_back(tokenizer.GetTokenString());
    while (tokenizer.GetNext() == COMMANDLINE_VALUE)
        argumentValues.push_back(tokenizer.GetTokenString());

    vector<string>::iterator valueIter = argumentValues.begin();
    for (ArgumentVectorIter argIter = arguments.begin(); argIter != arguments.end(); ++argIter) {
        
        CommandArgument &argument = *argIter;

        int i = 0;
        for (; i < argument.MaxInstances && valueIter != argumentValues.end(); ++i) {
            result->Arguments[argument.Name].push_back(*valueIter);
            ++valueIter;
        }

        if (i < argument.MinInstances)
            result->NumErrors++;

    }

    return result;

}

const string CommandLine::GetExecutablePath(const string &commandLine) {

    CommandLineTokenizer tokenizer(commandLine);

    CommandLineToken token = tokenizer.GetNext();

    return tokenizer.GetTokenString();

}

const string CommandLine::GetDescriptionString(ArgumentVector &arguments, OptionVector &options) {

    return "";

}