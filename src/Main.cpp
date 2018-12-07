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

#else // !OS_WIN

int main(int argc, const char *argv[]) {

    string commandLine = "";

#endif // OS_WIN

    CommandArgument arg1 = { "GameFilename", "Filename of the game to load at startup", 0, 1 };
    ArgumentVector argumentSpec = { arg1 };
    CommandOption opt1 = { COMMANDOPTION_VALUE, "platformConfig", "Filename of the platform configuration" };
    CommandOption opt2 = { COMMANDOPTION_VALUE, "engineConfig", "Filename of the engine configuration" };
    OptionVector optionSpec = { opt1, opt2 };

    unique_ptr<CommandLineResult> result(CommandLine::Parse(argumentSpec, optionSpec, commandLine));

    if (result.get()->NumErrors) {
        cerr << "Wrong use.\n" << CommandLine::GetDescriptionString(argumentSpec, optionSpec);
        return 0;
    }

    NameValueMap &options = result.get()->Options;    
    
    PlatformConfig *platformConfig = nullptr;
    if (options.count("platformConfig"))
        platformConfig = PlatformConfig::Load(*PugiXML::ParseDocument(options["platformConfig"]));
    else
        platformConfig = new DefaultPlatformConfig();
    unique_ptr<Platform> platform(Platform::Create(platformConfig));

    EngineConfig *engineConfig = nullptr;
    if (options.count("engineConfig"))
        engineConfig = new EngineConfig(options["engineConfig"]);
    else
        engineConfig = new DefaultEngineConfig();
    unique_ptr<Engine> engine(new Engine(*platform.get(), engineConfig));

    engine.get()->Initialize();
    
    engine.get()->LoadGame(result.get()->Arguments["GameFilename"][0]);

    return 0;

}
