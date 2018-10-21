/*
File: Main.cpp
Author: Lars Vidar Magnusson
*/

#include "GaME.h"

/*
 * Program entry.
 *
 * Usage: game ENGINECONFIG GAMESPEC
 */
#ifdef OS_WIN

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    string commandLine = GetCommandLineA();

#endif // OS_WIN
#ifdef OS_XLIB

int main(int argc, const char *argv[]) {

    string commandLine = "";

#endif // OS_XLIB

    CommandArgument arg1 = { "GameFilename", "Filename of the game to load at startup", 0, 1 };
    ArgumentVector argumentSpec = { arg1 };
    CommandOption opt1 = { COMMANDOPTION_VALUE, "config", "Filename of the engine configuration" };
    OptionVector optionSpec = { opt1 };

    unique_ptr<CommandLineResult> result(CommandLine::Parse(argumentSpec, optionSpec, commandLine));

    if (result.get()->NumErrors) {
        cerr << "Wrong use.\n" << CommandLine::GetDescriptionString(argumentSpec, optionSpec);
        return 0;
    }

    NameValueMap &options = result.get()->Options;    
    
    EngineConfig *config = EngineConfig::Load(options.count("config") ? options["config"] : "engine.config");

    unique_ptr<Platform> platform(Platform::Load(config->GetPlatformConfig()));
    
    unique_ptr<Engine> engine(new Engine(*platform.get(), *config));
    engine.get()->Initialize();
    
    engine.get()->LoadGame(result.get()->Arguments["GameFilename"][0]);

    return 0;
}
