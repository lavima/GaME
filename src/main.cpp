/*
File: Main.cpp
Author: Lars Vidar Magnusson
*/

#include "game.h"

using namespace game;
using namespace game::lib;

/*
 * Program entry.
 *
 * Usage: game[.exe] [OPTIONS...] GAMESPEC
 */
#ifdef PLATFORM_WIN32

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    string commandLine = GetCommandLineA();

#else // !OS_WIN

int main(int argc, const char *argv[]) {

    std::vector<std::string> arguments;
    for (int i=0; i<argc; ++i)
        arguments.push_back(std::string(argv[i]));

#endif // OS_WIN

    CommandLine::SpecifyArgument("GAME_FILE", "Filename of the game to load at startup", 0, 1);
    CommandLine::SpecifyOption(COMMANDOPTION_VALUE, "engineConfig", "Filename of the engine configuration");
    CommandLine::SpecifyOption(COMMANDOPTION_VALUE, "engineLog", "The filename of the engine log");
    CommandLine::SpecifyOption(COMMANDOPTION_VALUE, "gameDirectory", "The directory to use as the root directory");

    if (!CommandLine::Parse(arguments)) {
        LOG_INFO(CommandLine::GetUsageString().c_str());
        return 0;
    }

    Engine engine;

    if (!engine.Initialize()) {
        LOG_ERROR("Couldn't initialize engine");
        return 0;
    }

    
    if (!engine.LoadGame(CommandLine::GetArgument("GAME_FILE")[0])) {
        LOG_ERROR("Couldn't load game");
        return 0;
    }
    
    engine.Run();

    return 1;

}
