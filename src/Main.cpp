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

    vector<string> argumentValues;
    for (int i=0; i<argc; ++i)
        argumentValues.push_back(string(argv[i]));

#endif // OS_WIN

    CommandLine::SpecifyArgument("GAME_FILE", "Filename of the game to load at startup", 0, 1);
    CommandLine::SpecifyOption(COMMANDOPTION_VALUE, "platformConfig", "Filename of the platform configuration");
    CommandLine::SpecifyOption(COMMANDOPTION_VALUE, "engineConfig", "Filename of the engine configuration");
    CommandLine::SpecifyOption(COMMANDOPTION_VALUE, "engineLogFilename", "The file to store the engine log");
    CommandLine::SpecifyOption(COMMANDOPTION_VALUE, "gameDirectory", "The directory to use as the root directory");

    if (!CommandLine::Parse(argumentValues)) {
        cout << CommandLine::GetUsageString() << endl;
        return 0;
    }

    Engine engine;

    engine.Initialize();
    
    engine.LoadGame(CommandLine::GetArgument("GAME_FILE")[0]);

    return 0;

}
